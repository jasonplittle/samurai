#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"

#include "MobManager.hpp"

#include "World.hpp"
#include "BackgroundParallax.hpp"
#include "Props.hpp"

#include "SpriteRenderer.hpp"

#include "IGameplayContext.hpp"
#include "GameInput.hpp"

#include "HitboxManager.hpp"
#include "ProjectileManager.hpp"


struct Inputs // For sandbox only
{
    bool t;
    bool m;

    bool lMouse;
    bool rMouse;
    glm::vec2 mousePos;
};


class Game : public IGameplayContext
{
public:
    Game(GameInput& gameInput);

    void Init();
    void ReadInput(glm::ivec2 windowSize, Inputs inputs);
    void Update(float dt);
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
    std::shared_ptr<Character> m_player;
    PlayerController m_playerController;

    MobManager m_mobManager;
    
    HitboxManager m_hitboxManager;
    ProjectileManager m_projectileManager;

    PhysicsSystem m_physics;

    World m_world;
    BackgroundParallax m_background;
    Props m_props;

    OrthographicCamera m_camera;
    SpriteRenderer m_renderer;
};
