#include "Game.hpp"

#include "SamuraiCharacterFactory.hpp"
#include "ExecutionerCharacterFactory.hpp"
#include "ForestTilesetFactory.hpp"
#include "ForestBackdropParallaxFactory.hpp"
#include "ForestPropsetFactory.hpp"

#include "FeudalJapanBackdropParallaxFactory.hpp"
#include "FeudalJapanTilesetFactory.hpp"


constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };

Game::Game(GameInput& gameInput)
    :
    m_world(FeudalJapanTilesetFactory::CreateTileSet()), 
    m_background(FeudalJapanBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y)),
    m_props(ForestPropsetFactory::CreatePropset()),
    m_player(std::move(SamuraiCharacterFactory::CreateSamuraiCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y), *this))),
    m_playerController(m_player, gameInput)
{
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
    glm::vec2 mouseWorldPos = 
    {
        (inputs.mousePos.x / (windowSize.x / VIRTUAL_SCEEEN.x)) - (m_camera.Size.x * 0.5) + m_camera.Pos.x, 
        (((windowSize.y - inputs.mousePos.y) / (windowSize.y / VIRTUAL_SCEEEN.y)) - (m_camera.Size.y * 0.5) + m_camera.Pos.y) 
    };

    if (inputs.t)
    {
        m_props.AddProp(mouseWorldPos.x, m_world);
    }

    if (inputs.m)
    {
        m_mobManager.AddMob(mouseWorldPos, *this);
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
    m_playerController.Update(dt);
    m_physics.UpdateBody(m_player->Body(), m_world, dt);
    m_player->Update(dt, m_hitboxManager);
    m_mobManager.Update(dt, *m_player, m_world, m_physics, m_hitboxManager);
    m_projectileManager.Update(dt, m_physics, m_world);
    m_hitboxManager.Update(dt);

    m_camera.Pos.x = std::max(m_player->Body().Position.x, VIRTUAL_SCEEEN.x * 0.5f);
}


void Game::Render()
{
    m_background.DrawLayers(m_renderer, m_camera);
    m_props.DrawProps(m_renderer, m_camera);
    m_projectileManager.DrawProjectiles(m_renderer, m_camera);
    m_world.DrawTiles(m_renderer, m_camera);
    m_hitboxManager.DrawHitboxes(m_renderer, m_camera);
    m_mobManager.DrawMobs(m_renderer, m_camera);

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
