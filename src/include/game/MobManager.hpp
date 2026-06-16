#pragma once

#include "Character.hpp"
#include "MobController.hpp"
#include "PhysicsSystem.hpp"
#include "Hitbox.hpp"


struct Mob
{
    std::shared_ptr<Character> Character;
    std::unique_ptr<MobController> Controller;
};


class MobManager
{
public:
    void AddMob(glm::vec2 position, IGameplayContext& context);
    void Update(float dt, Character& player, const World& world, PhysicsSystem& physics, std::vector<Hitbox>& hitboxes);
    void DrawMobs(SpriteRenderer& renderer, OrthographicCamera camera);

private:
    std::vector<Mob> m_mobs;
    float m_spawnThrottleTimer = 0.0;
};
