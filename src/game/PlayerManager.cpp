#include "PlayerManager.hpp"
#include "SamuraiCharacterFactory.hpp"


void PlayerManager::AddPlayer(glm::vec2 position, IGameplayContext& context, GameInput& gameInput)
{
    auto player = std::shared_ptr<Character>(SamuraiCharacterFactory::CreateCharacter(position, context));
    m_controller = std::make_unique<PlayerController>(player, gameInput);
    m_players.push_back(player);
}

void PlayerManager::Update(float dt, const World& world, PhysicsSystem& physics, HitboxManager& hitboxManager, IGameplayContext& context)
{
    m_controller->Update(dt);

    for (auto& player : m_players)
    {
        physics.UpdateBody(player->Body(), world, dt);
        player->Update(dt, hitboxManager);
    }
    
    if (m_players.back()->IsFullDead())
    {
        context.PlayerDied();
    }
}

void PlayerManager::DrawPlayers(SpriteRenderer& renderer, OrthographicCamera camera)
{
    for (auto& player : m_players)
    {
        renderer.Render(
            player->Animator().GetCurrentSprite(),
            glm::ivec2(player->Animator().GetCurrentFrame(), 0), 
            !player->IsFacingRight() ^ player->Animator().FlipX(),
            camera,
            player->Body().Position - player->Animator().GetFrameCenterOffset(),
            player->Animator().GetFrameSize(),
            player->DeathDecay()
        );
    }
}