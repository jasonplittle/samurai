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


Game::Game()
    :
    m_world(ForestTilesetFactory::CreateTileSet()), 
    m_background(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y)),
    m_props(std::move(ForestPropsetFactory::CreatePropset()))
{
    m_camera =
    {
        .Pos = glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y * 0.5),
        .Size = VIRTUAL_SCEEEN,
        .Zoom = 1
    };
}


void Game::Init(std::shared_ptr<GameInput> gameInput)
{
    m_gameInput = gameInput;
    m_playerManager.AddPlayer(m_camera.Pos, *this, *m_gameInput);
    m_world.CreateDefaultWorld();
}


void Game::Update(float dt, int windowWidth, int windowHeight)
{
    m_worldEditior.Update(windowWidth, windowHeight, m_camera, *m_gameInput, m_props, m_world, m_mobManager, m_lights, *this);
    m_playerManager.Update(dt, m_world, m_physics, m_hitboxManager);
    m_props.Update(dt);
    m_mobManager.Update(dt, m_playerManager.Player(), m_world, m_physics, m_hitboxManager);
    m_projectileManager.Update(dt, m_physics, m_world);
    m_hitboxManager.Update(dt);
    m_fog.Update(dt);
    m_lights.Update(dt);
    m_hud.Update(dt, m_playerManager.Player(), m_mobManager);

    m_camera.Pos.x = std::max(m_playerManager.Player().Body().Position.x, VIRTUAL_SCEEEN.x * 0.5f);
}


void Game::Render()
{
    m_background.DrawLayers(m_spriteRenderer, m_camera);
    m_fog.DrawFog(m_noiseRenderer, m_camera, glm::vec2(0, 0), 0.9, 0.32);
    m_props.DrawProps(m_spriteRenderer, m_camera);
    m_projectileManager.DrawProjectiles(m_spriteRenderer, m_camera);
    m_world.DrawTiles(m_spriteRenderer, m_camera);
    m_hitboxManager.DrawHitboxes(m_spriteRenderer, m_camera);
    m_mobManager.DrawMobs(m_spriteRenderer, m_camera);
    m_playerManager.DrawPlayers(m_spriteRenderer, m_camera);
    m_renderer.EnableAdditiveBlending();
    m_lights.DrawLights(m_spriteRenderer, m_camera);
    m_renderer.EnableBlending();
    m_fog.DrawFog(m_noiseRenderer, m_camera, glm::vec2(20, 20), 0.8, 0.32);
    m_hud.DrawHUD(m_quadRenderer, m_camera);
    
}
