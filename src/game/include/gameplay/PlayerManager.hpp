#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"
#include "PhysicsSystem.hpp"
#include "HitboxManager.hpp"



class PlayerManager
{
public:
    void AddPlayer(glm::vec2 position, IGameplayContext& context, GameInput& gameInput);
    void Update(float dt, const World& world, PhysicsSystem& physics, HitboxManager& hitboxManager, IGameplayContext& context);
    void DrawPlayers(SpriteRenderer& renderer, OrthographicCamera camera);

    Character& Player() const { return *m_players.back(); }

private:
    std::vector<std::shared_ptr<Character>> m_players;
    std::unique_ptr<PlayerController> m_controller;
};
