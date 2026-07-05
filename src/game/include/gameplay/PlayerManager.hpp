#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"
#include "PhysicsSystem.hpp"
#include "HitboxManager.hpp"



class PlayerManager
{
public:
    void AddPlayer(glm::vec2 position, IGameplayContext& context, GameInput& gameInput);
    void Update(float dt, const World& world, PhysicsSystem& physics, HitboxManager& hitboxManager);
    void DrawPlayers(SpriteRenderer& renderer, OrthographicCamera camera);

    Character& Player() const { return *m_player; }

private:
    std::shared_ptr<Character> m_player;
    std::unique_ptr<PlayerController> m_controller;
};
