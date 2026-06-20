#include "GameInput.hpp"
#include <iostream>

constexpr double DoublePressWindow = 0.25;


void InputSystem::BeginFrame(float dt)
{
    m_time += dt;

    for (auto& [key, state] : m_keys)
    {
        state.Pressed = false;
        state.Released = false;
        state.DoublePressed = false;

        if (state.Down)
        {
            state.HeldTime += dt;
        }
        else
        {
            state.HeldTime = 0.0f;
        }
    }
}

void InputSystem::OnKeyPressed(int key)
{
    auto& state = m_keys[key];

    if (!state.Down)
    {
        state.Pressed = true;
        state.DoublePressed = (m_time - state.LastPressedTime) < DoublePressWindow;
        state.LastPressedTime = m_time;
    }

    state.Down = true;
}

void InputSystem::OnKeyReleased(int key)
{
    auto& state = m_keys[key];

    state.Down = false;
    state.Released = true;
}

bool InputSystem::Pressed(int key) const
{
    auto it = m_keys.find(key);

    return it != m_keys.end() &&
           it->second.Pressed;
}

bool InputSystem::Released(int key) const
{
    auto it = m_keys.find(key);

    return it != m_keys.end() &&
           it->second.Released;
}

bool InputSystem::Held(int key) const
{
    auto it = m_keys.find(key);

    return it != m_keys.end() &&
           it->second.Down;
}

bool InputSystem::DoublePressed(int key) const
{
    auto it = m_keys.find(key);

    return it != m_keys.end() &&
           it->second.DoublePressed;
}