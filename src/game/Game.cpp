#include "Game.hpp"

#include "SamuraiCharacterFactory.hpp"
#include "ExecutionerCharacterFactory.hpp"
#include "ForestTilesetFactory.hpp"
#include "ForestBackdropParallaxFactory.hpp"
#include "ForestPropsetFactory.hpp"


constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };

Game::Game()
    :
    m_world(ForestTilesetFactory::CreateTileSet()), 
    m_background(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y)),
    m_props(ForestPropsetFactory::CreatePropset()),
    m_player(std::move(SamuraiCharacterFactory::CreateSamuraiCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y), *this))),
    m_mob(std::move(ExecutionerCharacterFactory::CreateExecutionerCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5 + 50, VIRTUAL_SCEEEN.y), *this)))
{

    m_mobController = std::make_unique<MobController>(m_mob);
    // m_player = 
    // m_mob = std::make_shared<Character>(ExecutionerCharacterFactory::CreateExecutionerCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5 + 50, VIRTUAL_SCEEEN.y), *this));

    m_camera =
    {
        .Pos = glm::vec2(m_player->Body().Position.x, VIRTUAL_SCEEEN.y * 0.5),
        .Size = VIRTUAL_SCEEEN,
        .Zoom = 1
    };
}


void Game::Init()
{
    m_world.CreateDefaultWorld();
}


void Game::ReadInput(glm::ivec2 windowSize, Inputs inputs)
{
    m_playerInput.primary = inputs.space;
    m_playerInput.up = inputs.up;
    m_playerInput.down = inputs.down;
    m_playerInput.left = inputs.left;
    m_playerInput.right = inputs.right;

    // m_player2Input.primary = inputs.f;
    // m_player2Input.up = inputs.w;
    // m_player2Input.down = inputs.s;
    // m_player2Input.left = inputs.a;
    // m_player2Input.right = inputs.d;

    glm::vec2 mouseWorldPos = 
    {
        (inputs.mousePos.x / (windowSize.x / VIRTUAL_SCEEEN.x)) - (m_camera.Size.x * 0.5) + m_camera.Pos.x, 
        (((windowSize.y - inputs.mousePos.y) / (windowSize.y / VIRTUAL_SCEEEN.y)) - (m_camera.Size.y * 0.5) + m_camera.Pos.y) 
    };

    if (inputs.t)
    {
        m_props.AddProp(mouseWorldPos.x, m_world);
    }

    if (inputs.lMouse)
    {
        m_world.ShowTile(true, mouseWorldPos.x, mouseWorldPos.y);
    }
    if (inputs.rMouse)
    {
        m_world.ShowTile(false, mouseWorldPos.x, mouseWorldPos.y);
    }
}


void Game::Update(float dt)
{
    m_playerController.Update(dt, *m_player, m_playerInput);
    // m_playerController.Update(dt, *m_mob, m_playerInput);
    m_mobController->Update(dt, *m_player, m_world);

    m_physics.UpdateBody(m_player->Body(), m_world, dt);
    m_physics.UpdateBody(m_mob->Body(), m_world, dt);

    m_player->Update(dt, m_hitboxes);
    m_mob->Update(dt, m_hitboxes);

    updateHitboxes(dt);

    m_camera.Pos.x = std::max(m_player->Body().Position.x, VIRTUAL_SCEEEN.x * 0.5f);
}


void Game::Render()
{
    m_background.DrawLayers(m_renderer, m_camera);
    m_props.DrawProps(m_renderer, m_camera);
    m_world.DrawTiles(m_renderer, m_camera);
    

    // std::unique_ptr<Sprite> spr = std::make_unique<Sprite>("resources/world/Tileset.png", glm::vec2(32, 32));

    // for (auto& hitbox : m_hitboxes)
    // {
    //     m_renderer.Render(
    //         *spr,
    //         glm::ivec2(1, 4), 
    //         false,
    //         m_camera,
    //         glm::vec2((hitbox.Bounds().Left + hitbox.Bounds().Right) / 2, (hitbox.Bounds().Bottom + hitbox.Bounds().Top) / 2),
    //         glm::vec2(hitbox.Bounds().Right - hitbox.Bounds().Left, hitbox.Bounds().Bottom - hitbox.Bounds().Top)
    //     );
    // }

    // m_renderer.Render(
    //     *spr,
    //     glm::ivec2(1, 4), 
    //     false,
    //     m_camera,
    //     glm::vec2((m_player2->Hurtbox().Left + m_player2->Hurtbox().Right) / 2, (m_player2->Hurtbox().Bottom + m_player2->Hurtbox().Top) / 2),
    //     glm::vec2(m_player2->Hurtbox().Right - m_player2->Hurtbox().Left, m_player2->Hurtbox().Bottom - m_player2->Hurtbox().Top)
    // );

    // m_renderer.Render(
    //     *spr,
    //     glm::ivec2(1, 4), 
    //     false,
    //     m_camera,
    //     glm::vec2((m_player1->Hurtbox().Left + m_player1->Hurtbox().Right) / 2, (m_player1->Hurtbox().Bottom + m_player1->Hurtbox().Top) / 2),
    //     glm::vec2(m_player1->Hurtbox().Right - m_player1->Hurtbox().Left, m_player1->Hurtbox().Bottom - m_player1->Hurtbox().Top)
    // );

    m_renderer.Render(
        m_mob->Animator().GetCurrentSprite(),
        glm::ivec2(m_mob->Animator().GetCurrentFrame(), 0), 
        !m_mob->IsFacingRight() ^ m_mob->Animator().FlipX(),
        m_camera,
        m_mob->Body().Position - m_mob->Animator().GetFrameCenterOffset(),
        m_mob->Animator().GetFrameSize(),
        m_mob->DeathDecay()
    );

    m_renderer.Render(
        m_player->Animator().GetCurrentSprite(),
        glm::ivec2(m_player->Animator().GetCurrentFrame(), 0), 
        !m_player->IsFacingRight() ^ m_player->Animator().FlipX(),
        m_camera,
        m_player->Body().Position - m_player->Animator().GetFrameCenterOffset(),
        m_player->Animator().GetFrameSize(),
        m_player->DeathDecay()
    );
}


void Game::updateHitboxes(float dt)
{
    for (auto it = m_hitboxes.begin(); it != m_hitboxes.end(); )
    {
        it->Lifetime -= dt;

        if (it->Lifetime <= 0.0)
        {
            it = m_hitboxes.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
