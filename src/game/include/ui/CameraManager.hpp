#pragma once

#include "Camera.hpp"
#include "Character.hpp"


class CameraManager
{
public:

    CameraManager(OrthographicCamera camera) : m_camera(camera) {}

    void Update(float dt, Character& player)
    {
        float deadZone = 75.0f;

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

        float t = 1.0f - std::exp(-5.0f * dt);

        m_camera.Pos.x += (targetX - m_camera.Pos.x) * t;
    }

    OrthographicCamera& Camera() { return m_camera; }

private:
    OrthographicCamera m_camera;
};
