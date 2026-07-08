#pragma once

#include "Camera.hpp"
#include "Character.hpp"

#include <algorithm>


class CameraManager
{
public:

    CameraManager(OrthographicCamera camera) : m_camera(camera) { m_virtualCameraX = camera.Pos.x; }

    void Update(float dt, Character& player)
    {
        float deadZone = 75.0f;

        float left  = m_virtualCameraX - deadZone * 0.5f;
        float right = m_virtualCameraX + deadZone * 0.5f;

        float targetX = m_virtualCameraX;

        float playerX = player.Body().Position.x;

        if (playerX < left)
        {
            targetX = playerX + deadZone * 0.5f;
        }
        else if (playerX > right)
        {
            targetX = playerX - deadZone * 0.5f;
        }

        float t = 1.0f - std::exp(-3.0f * dt);
        m_virtualCameraX += (targetX - m_virtualCameraX) * t;

        m_camera.Pos.x = playerX + (playerX - m_virtualCameraX);
        // m_camera.Pos.x = m_virtualCameraX;
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

        renderer.Render(
            *m_sprite,
            glm::ivec2(0, 0),
            false,
            m_camera,
            glm::vec2(m_virtualCameraX, m_camera.Pos.y),
            glm::vec2(16, 16),
            1.f
        );
    }

    OrthographicCamera& Camera() { return m_camera; }

private:
    OrthographicCamera m_camera;

    float m_virtualCameraX = 0;

};
