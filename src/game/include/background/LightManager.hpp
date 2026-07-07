#pragma once

#include <glm/glm.hpp>
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "Animator.hpp"


struct Light
{
    glm::vec2 Position;

    glm::vec3 Color =
    {
        0.8f,
        0.6f,
        0.4f
    };

    float Radius = 64.f;

    float Intensity = 0.5f;

    std::unique_ptr<AnimationPlayer> Animator;
};


class LightManager
{
public:

    void Add(Light& light)
    {
        light.Animator = std::make_unique<AnimationPlayer>(m_lightAnimation);
        std::unique_ptr<Light> lightptr = std::make_unique<Light>(std::move(light));
        m_lights.push_back(std::move(lightptr));
    }

    void Update(float dt);
    void DrawLights(SpriteRenderer& renderer, OrthographicCamera camera);

private:
    std::vector<std::unique_ptr<Light>> m_lights;
    std::unique_ptr<Sprite> m_lightSprite = std::make_unique<Sprite>("resources/atmosphere/light.png", glm::vec2(256, 256));
    
    AnimationClip m_lightAnimation = 
    {
        .StartFrame = 0,
        .FrameCount = 4,
        .FrameDuration = 0.08,
        .Loop = true,
        .FrameSize = glm::vec2(128, 128),
        .Sprite = std::make_unique<Sprite>("resources/atmosphere/lights/8.png", glm::vec2(128, 128))
    };

    float m_time = 0;
};
