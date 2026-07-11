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
    m_props(std::move(ForestPropsetFactory::CreatePropset())),
    m_cameraManager({
        .Pos = glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y * 0.5),
        .Size = VIRTUAL_SCEEEN,
        .Zoom = 1
    })
{}


void Game::Init(std::shared_ptr<GameInput> gameInput)
{
    m_gameInput = gameInput;
    m_playerManager.AddPlayer(m_cameraManager.Camera().Pos, *this, *m_gameInput);
    m_world.CreateDefaultWorld();
}

void Game::Reset()
{
    
}

void Game::PlayerDied()
{
    m_playerManager.AddPlayer(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y * 0.5), *this, *m_gameInput);
}


void Game::Update(float realDt, int windowWidth, int windowHeight)
{
    float gameDt = realDt;

    m_hitstopManager.Update(realDt);

    if (m_hitstopManager.Active())
        gameDt = 0.f;

    m_worldEditior.Update(windowWidth, windowHeight, m_cameraManager.Camera(), *m_gameInput, m_props, m_world, m_mobManager, m_lights, *this);
    
    m_playerManager.Update(gameDt, m_world, m_physics, m_hitboxManager, *this);
    m_props.Update(gameDt);
    m_mobManager.Update(gameDt, m_playerManager.Player(), m_world, m_physics, m_hitboxManager);
    m_projectileManager.Update(gameDt, m_physics, m_world);
    m_hitboxManager.Update(gameDt);

    m_fog.Update(gameDt);
    m_lights.Update(gameDt);

    m_hud.Update(realDt, m_playerManager.Player(), m_mobManager);
    m_cameraManager.Update(realDt, m_playerManager.Player());
}


void Game::Render()
{
    m_background.DrawLayers(m_spriteRenderer, m_cameraManager.Camera());
    m_fog.DrawFog(m_noiseRenderer, m_cameraManager.Camera(), glm::vec2(0, 0), 0.4, 0.32);
    m_props.DrawProps(m_spriteRenderer, m_cameraManager.Camera());
    m_projectileManager.DrawProjectiles(m_spriteRenderer, m_cameraManager.Camera());
    m_world.DrawTiles(m_spriteRenderer, m_cameraManager.Camera());
    m_hitboxManager.DrawHitboxes(m_spriteRenderer, m_cameraManager.Camera());
    m_mobManager.DrawMobs(m_spriteRenderer, m_cameraManager.Camera());
    m_playerManager.DrawPlayers(m_spriteRenderer, m_cameraManager.Camera());
    m_renderer.EnableAdditiveBlending();
    m_lights.DrawLights(m_spriteRenderer, m_cameraManager.Camera());
    m_renderer.EnableBlending();
    m_fog.DrawFog(m_noiseRenderer, m_cameraManager.Camera(), glm::vec2(20, 20), 0.8, 0.32);
    m_hud.DrawHUD(m_quadRenderer, m_cameraManager.Camera());
    m_cameraManager.DrawCamera(m_spriteRenderer);
    
}
