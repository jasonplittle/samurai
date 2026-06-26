#include "MobManager.hpp"
#include "ExecutionerCharacterFactory.hpp"
#include "ArcherCharacterFactory.hpp"

#include <random>



void MobManager::AddMob(glm::vec2 position, IGameplayContext& context)
{
    if (m_spawnThrottleTimer >= 2.0f)
    {
        m_spawnThrottleTimer = 0.0;

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> dist(1, 6);
        int value = dist(rng); // 1..10 inclusive

        std::shared_ptr<Character> character;

        switch (value)
        {
            case 1: 
            case 2: 
            case 3:
                character = ExecutionerCharacterFactory::CreateCharacter(position, context);
                break;

            case 4:
                character = ArcherCharacterFactory::CreateCharacter(position, context, ArcherColor::Green);
                break;

            case 5:
                character = ArcherCharacterFactory::CreateCharacter(position, context, ArcherColor::Red);
                break;

            case 6:
                character = ArcherCharacterFactory::CreateCharacter(position, context, ArcherColor::Blue);
                break;
        }
        
        std::unique_ptr<MobController> controller = std::make_unique<MobController>(character);

        m_mobs.emplace_back(Mob {std::move(character), std::move(controller)});
    }
}

void MobManager::Update(float dt, Character& player, const World& world, PhysicsSystem& physics, HitboxManager& hitboxManager)
{
    for (auto& mob : m_mobs)
    {
        mob.Controller->Update(dt, player, world);
        physics.UpdateBody(mob.Character->Body(), world, dt);
        mob.Character->Update(dt, hitboxManager);
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
