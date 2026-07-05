#include "PlayerManager.hpp"
#include "SamuraiCharacterFactory.hpp"


void PlayerManager::AddPlayer(glm::vec2 position, IGameplayContext& context, GameInput& gameInput)
{
    m_player = std::shared_ptr<Character>(SamuraiCharacterFactory::CreateCharacter(position, context));
    m_controller = std::make_unique<PlayerController>(m_player, gameInput);
}

void PlayerManager::Update(float dt, const World& world, PhysicsSystem& physics, HitboxManager& hitboxManager)
{
    m_controller->Update(dt);
    physics.UpdateBody(m_player->Body(), world, dt);
    m_player->Update(dt, hitboxManager);
}

void PlayerManager::DrawPlayers(SpriteRenderer& renderer, OrthographicCamera camera)
{
    renderer.Render(
        m_player->Animator().GetCurrentSprite(),
        glm::ivec2(m_player->Animator().GetCurrentFrame(), 0), 
        !m_player->IsFacingRight() ^ m_player->Animator().FlipX(),
        camera,
        m_player->Body().Position - m_player->Animator().GetFrameCenterOffset(),
        m_player->Animator().GetFrameSize(),
        m_player->DeathDecay()
    );
}