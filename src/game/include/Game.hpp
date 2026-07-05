#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"
#include "MobManager.hpp"
#include "World.hpp"
#include "BackgroundParallax.hpp"
#include "Props.hpp"
#include "WorldEditor.hpp"
#include "SpriteRenderer.hpp"
#include "QuadRenderer.hpp"
#include "IGameplayContext.hpp"
#include "GameInput.hpp"
#include "HitboxManager.hpp"
#include "ProjectileManager.hpp"
#include "GameHUD.hpp"
#include "PlayerManager.hpp"


class Game : public IGameplayContext
{
public:
    Game();

    void Init(std::shared_ptr<GameInput> gameInput);
    void Update(float dt, int windowWidth, int windowHeight);
    void Render();

    void SpawnHitbox(std::shared_ptr<Hitbox> hitbox) override
    {
        m_hitboxManager.AddHitbox(hitbox);
    }

    void SpawnProjectile(std::unique_ptr<Projectile>& projectile) override
    {
        m_hitboxManager.AddHitbox(projectile->Hitbox);
        m_projectileManager.AddProjectile(projectile);
    }

private:
    PlayerManager m_playerManager;

    std::shared_ptr<GameInput> m_gameInput;

    WorldEditor m_worldEditior;
    MobManager m_mobManager;
    
    HitboxManager m_hitboxManager;
    ProjectileManager m_projectileManager;

    PhysicsSystem m_physics;

    World m_world;
    BackgroundParallax m_background;
    Props m_props;

    GameHUD m_hud;

    OrthographicCamera m_camera;
    SpriteRenderer m_renderer;
    QuadRenderer m_quadRenderer;
};
