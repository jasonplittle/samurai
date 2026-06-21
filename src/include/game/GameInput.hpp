#pragma once

#include <unordered_map>


enum class Action
{
    MoveLeft,
    MoveRight,

    Jump,
    Down,

    Primary,
    Secondary,

    Slow
};


struct ButtonState
{
    bool Down = false;

    bool Pressed = false;
    bool Released = false;

    bool DoublePressed = false;

    float HeldTime = 0.0f;

    double LastPressedTime = -1000.0;
};


class InputSystem
{
public:
    void BeginFrame(float dt);

    void OnKeyPressed(int key);
    void OnKeyReleased(int key);

    bool Pressed(int key) const;
    bool Released(int key) const;
    bool Held(int key) const;
    bool DoublePressed(int key) const;

    float HeldTime(int key) const;

private:
    std::unordered_map<int, ButtonState> m_keys;
    double m_time = 0.0;
};


class ActionMap
{
public:

    void Bind(Action action, int key)
    {
        m_bindings[action] = key;
    }

    int GetKey(Action action) const
    {
        return m_bindings.at(action);
    }

private:
    std::unordered_map<Action, int> m_bindings;
};


class GameInput
{
public:
    GameInput(
        InputSystem& input,
        ActionMap actions)
        : m_input(input)
        , m_actions(actions)
    {
    }

    bool Pressed(Action action) const
    {
        return m_input.Pressed(
            m_actions.GetKey(action));
    }

    bool Released(Action action) const
    {
        return m_input.Released(
            m_actions.GetKey(action));
    }

    bool Held(Action action) const
    {
        return m_input.Held(
            m_actions.GetKey(action));
    }

    bool DoublePressed(Action action) const
    {
        return m_input.DoublePressed(
            m_actions.GetKey(action));
    }

private:
    InputSystem& m_input;
    ActionMap m_actions;
};