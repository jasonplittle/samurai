#include "LightManager.hpp"


void LightManager::Update(float dt)
{
    m_time += dt;

    for (auto& light : m_lights)
    {
        light->Animator->Update(dt);
    }
}

void LightManager::DrawLights(SpriteRenderer& renderer, OrthographicCamera camera)
{
    for (auto& light : m_lights)
    {
        renderer.Render(
            light->Animator->GetCurrentSprite(),
            glm::ivec2(light->Animator->GetCurrentFrame(), 0),
            false,
            camera,
            light->Position,
            glm::vec2(light->Radius * 2, light->Radius * 2),
            glm::vec4(light->Color.x, light->Color.y, light->Color.z, light->Intensity)
        );
    }
}