#include "Game.hpp"

#include "SamuraiCharacterFactory.hpp"
#include "ExecutionerCharacterFactory.hpp"
#include "ArcherCharacterFactory.hpp"
#include "ForestTilesetFactory.hpp"
#include "ForestBackdropParallaxFactory.hpp"
#include "ForestPropsetFactory.hpp"
#include "FeudalJapanBackdropParallaxFactory.hpp"
#include "FeudalJapanTilesetFactory.hpp"


constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };


Game::Game(GameInput& gameInput)
    :
    m_world(ForestTilesetFactory::CreateTileSet()), 
    m_background(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y)),
    m_props(std::move(ForestPropsetFactory::CreatePropset())),
    m_player(std::move(SamuraiCharacterFactory::CreateCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y), *this))),
    m_playerController(m_player, gameInput),
    m_gameInput(gameInput)
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


void Game::Update(float dt, int windowWidth, int windowHeight)
{
    m_worldEditior.Update(windowWidth, windowHeight, m_camera, m_gameInput, m_props, m_world, m_mobManager, *this);
    m_playerController.Update(dt);
    m_physics.UpdateBody(m_player->Body(), m_world, dt);
    m_props.Update(dt);
    m_player->Update(dt, m_hitboxManager);
    m_mobManager.Update(dt, *m_player, m_world, m_physics, m_hitboxManager);
    m_projectileManager.Update(dt, m_physics, m_world);
    m_hitboxManager.Update(dt);
    m_hud.Update(dt, *m_player);

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

    m_hud.DrawHUD(m_quadRenderer, m_camera);
}
