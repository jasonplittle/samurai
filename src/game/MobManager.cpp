#include "MobManager.hpp"
#include "ExecutionerCharacterFactory.hpp"


void MobManager::AddMob(glm::vec2 position, IGameplayContext& context)
{
    if (m_spawnThrottleTimer >= 2.0f)
    {
        m_spawnThrottleTimer = 0.0;
        
        std::shared_ptr<Character> character = ExecutionerCharacterFactory::CreateExecutionerCharacter(position, context);
        std::unique_ptr<MobController> controller = std::make_unique<MobController>(character);

        m_mobs.emplace_back(Mob {std::move(character), std::move(controller)});
    }
}

void MobManager::Update(float dt, Character& player, const World& world, PhysicsSystem& physics, std::vector<Hitbox>& hitboxes)
{
    for (auto& mob : m_mobs)
    {
        mob.Controller->Update(dt, player, world);
        physics.UpdateBody(mob.Character->Body(), world, dt);
        mob.Character->Update(dt, hitboxes);
    }

    m_spawnThrottleTimer += dt;
}

void MobManager::DrawMobs(SpriteRenderer& renderer, OrthographicCamera camera)
{
    for (auto& mob : m_mobs)
    {
        renderer.Render(
            mob.Character->Animator().GetCurrentSprite(),
            glm::ivec2(mob.Character->Animator().GetCurrentFrame(), 0), 
            !mob.Character->IsFacingRight() ^ mob.Character->Animator().FlipX(),
            camera,
            mob.Character->Body().Position - mob.Character->Animator().GetFrameCenterOffset(),
            mob.Character->Animator().GetFrameSize(),
            mob.Character->DeathDecay()
        );
    }
}
