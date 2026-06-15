#include "Game.hpp"

#include "SamuraiCharacterFactory.hpp"
#include "ExecutionerCharacterFactory.hpp"
#include "ForestTilesetFactory.hpp"
#include "ForestBackdropParallaxFactory.hpp"


constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };

Game::Game()
    :
    m_world(ForestTilesetFactory::CreateTileSet()), 
    m_background(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y))
{
    m_player1 = SamuraiCharacterFactory::CreateSamuraiCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y), *this);
    m_player2 = ExecutionerCharacterFactory::CreateExecutionerCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5 + 50, VIRTUAL_SCEEEN.y), *this);

    m_camera =
    {
        .Pos = glm::vec2(m_player1->Body().Position.x, VIRTUAL_SCEEEN.y * 0.5),
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
    m_player1Input.primary = inputs.space;
    m_player1Input.up = inputs.up;
    m_player1Input.down = inputs.down;
    m_player1Input.left = inputs.left;
    m_player1Input.right = inputs.right;

    m_player2Input.primary = inputs.f;
    m_player2Input.up = inputs.w;
    m_player2Input.down = inputs.s;
    m_player2Input.left = inputs.a;
    m_player2Input.right = inputs.d;

    glm::vec2 mouseWorldPos = 
    {
        (inputs.mousePos.x / (windowSize.x / VIRTUAL_SCEEEN.x)) - (m_camera.Size.x * 0.5) + m_camera.Pos.x, 
        (((windowSize.y - inputs.mousePos.y) / (windowSize.y / VIRTUAL_SCEEEN.y)) - (m_camera.Size.y * 0.5) + m_camera.Pos.y) 
    };

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
    m_playerController.Update(dt, *m_player1, m_player1Input);
    m_playerController.Update(dt, *m_player2, m_player2Input);

    m_physics.UpdateBody(m_player1->Body(), m_world, dt);
    m_physics.UpdateBody(m_player2->Body(), m_world, dt);

    m_player1->Update(dt, m_hitboxes);
    m_player2->Update(dt, m_hitboxes);

    updateHitboxes(dt);

    m_camera.Pos.x = std::max(m_player1->Body().Position.x, VIRTUAL_SCEEEN.x * 0.5f);
}


void Game::Render()
{
    m_background.RenderLayers(m_renderer, m_camera);
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
        m_player2->Animator().GetCurrentSprite(),
        glm::ivec2(m_player2->Animator().GetCurrentFrame(), 0), 
        !m_player2->IsFacingRight() ^ m_player2->Animator().FlipX(),
        m_camera,
        m_player2->Body().Position - m_player2->Animator().GetFrameCenterOffset(),
        m_player2->Animator().GetFrameSize(),
        m_player2->DeathDecay()
    );

    m_renderer.Render(
        m_player1->Animator().GetCurrentSprite(),
        glm::ivec2(m_player1->Animator().GetCurrentFrame(), 0), 
        !m_player1->IsFacingRight() ^ m_player1->Animator().FlipX(),
        m_camera,
        m_player1->Body().Position - m_player1->Animator().GetFrameCenterOffset(),
        m_player1->Animator().GetFrameSize(),
        m_player1->DeathDecay()
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
