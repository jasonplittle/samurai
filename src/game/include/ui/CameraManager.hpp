#pragma once

#include "Camera.hpp"
#include "Character.hpp"

#include <algorithm>


class CameraManager
{
public:

    CameraManager(OrthographicCamera camera) : m_camera(camera) {}

    void Update(float dt, Character& player)
    {
        float deadZone = 75.0f;

        // How far ahead the camera looks
        float lookAhead = player.Body().Velocity.x * 0.3f;
        lookAhead = std::clamp(lookAhead, -150.0f, 150.0f);

        float left  = m_camera.Pos.x - deadZone * 0.5f;
        float right = m_camera.Pos.x + deadZone * 0.5f;

        float targetX = m_camera.Pos.x;

        float playerX = player.Body().Position.x;

        if (playerX < left)
        {
            targetX = playerX + deadZone * 0.5f;
        }
        else if (playerX > right)
        {
            targetX = playerX - deadZone * 0.5f;
        }

        targetX += lookAhead;

        float t = 1.0f - std::exp(-5.0f * dt);

        m_camera.Pos.x += (targetX - m_camera.Pos.x) * t;
    }

    
    void DrawCamera(SpriteRenderer& renderer)
    {
        return;

        static std::unique_ptr<Sprite> m_sprite = std::make_unique<Sprite>("resources/props/BlackSquare.png", glm::vec2(32, 32));

        renderer.Render(
            *m_sprite,
            glm::ivec2(0, 0),
            false,
            m_camera,
            m_camera.Pos,
            glm::vec2(16, 16),
            0.5
        );
    }

    OrthographicCamera& Camera() { return m_camera; }

private:
    OrthographicCamera m_camera;

};
