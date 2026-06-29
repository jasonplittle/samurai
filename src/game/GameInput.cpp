#include "GameInput.hpp"
#include <iostream>

constexpr double DoublePressWindow = 0.25;
constexpr float AxisPressMargin = 0.45f;


void InputSystem::BeginFrame(float dt)
{
    m_time += dt;

    for (auto& [key, state] : m_buttons)
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
    auto& state = m_buttons[key];

    if (!state.Down)
    {
        state.Pressed = true;
        state.DoublePressed = (m_time - state.LastPressedTime) < DoublePressWindow;
        state.LastPressedTime = m_time;
        state.Axis = 1.0f;
    }

    state.Down = true;
}


void InputSystem::OnKeyReleased(int key)
{
    auto& state = m_buttons[key];

    state.Down = false;
    state.Released = true;
    state.Axis = 0.0f;
}


void InputSystem::UpdateAxis(int key, float val)
{
    auto& state = m_buttons[key];

    if (std::abs(val) < AxisPressMargin)
    {
        if (std::abs(state.Axis) >= AxisPressMargin)
        {
            OnKeyPressed(key);
        }
    } 
    else
    {
        if (std::abs(state.Axis) < AxisPressMargin)
        {
            OnKeyReleased(key);
        }
    }

    state.Axis = val;
}


bool InputSystem::Pressed(int key) const
{
    auto it = m_buttons.find(key);

    return it != m_buttons.end() &&
           it->second.Pressed;
}


bool InputSystem::Released(int key) const
{
    auto it = m_buttons.find(key);

    return it != m_buttons.end() &&
           it->second.Released;
}



bool InputSystem::Held(int key) const
{
    auto it = m_buttons.find(key);

    return it != m_buttons.end() &&
           it->second.Down;
}


bool InputSystem::DoublePressed(int key) const
{
    auto it = m_buttons.find(key);

    return it != m_buttons.end() &&
           it->second.DoublePressed;
}


float InputSystem::GetAxis(int key) const
{
    auto it = m_buttons.find(key);

    return it != m_buttons.end() ? it->second.Axis : 0.0f;
}
