#pragma once

#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>


constexpr int KEYBOARD_OFFSET = 0;
constexpr int GAMEPAD_OFFSET  = 10000;
constexpr int GAMEPAD_AXIS_OFFSET  = 20000;
constexpr int MOUSE_OFFSET  = 30000;


enum class Action
{
    MoveX,
    MoveLeft,
    MoveRight,

    Jump,
    Down,

    Primary,
    Secondary,
    Throw,
    Ultimate,

    Heal,

    Slow,
    Dash,

    PlaceTile,
    RemoveTile,
    PlaceMob,
    PlaceProp,
    PlaceLight
};


enum class InputType
{
    KeyboardKey,
    GamepadButton,
    GamepadAxis,
    MouseButton,
};


struct InputBinding
{
    InputType Type;
    int Code;
};


class ActionMap
{
public:
    void Bind(Action action, InputBinding binding)
    {
        m_bindings[action].push_back(binding);
    }

    const std::vector<InputBinding>& GetBindings(Action action) const
    {
        return m_bindings.at(action);
    }

private:
    std::unordered_map<Action, std::vector<InputBinding>> m_bindings;
};


struct ButtonState
{
    bool Down = false;

    bool Pressed = false;
    bool Released = false;

    bool DoublePressed = false;

    float HeldTime = 0.0f;

    double LastPressedTime = -1000.0;

    float Axis = 0.0f;
};


class InputSystem
{
public:
    void BeginFrame(float dt);

    void OnKeyPressed(int key);
    void OnKeyReleased(int key);
    void UpdateAxis(int key, float val);

    bool Pressed(int key) const;
    bool Released(int key) const;
    bool Held(int key) const;
    bool DoublePressed(int key) const;
    float GetAxis(int key) const;
    
    float HeldTime(int key) const;

    void SetCursor(double x, double y) { m_cursorX = x; m_cursorY = y; }
    double GetCursorX() { return m_cursorX; }
    double GetCursorY() { return m_cursorY; }

private:
    std::unordered_map<int, ButtonState> m_buttons;

    double m_cursorX;
    double m_cursorY;

    double m_time = 0.0;

};


class GameInput
{
public:
    GameInput(InputSystem& input, ActionMap actions) : m_input(input), m_actions(actions) {}

    bool Pressed(Action action) const
    {
        for (auto& binding : m_actions.GetBindings(action))
        {
            if (m_input.Pressed(ToId(binding)))
                return true;
        }

        return false;
    }

    bool Released(Action action) const
    {
        for (auto& binding : m_actions.GetBindings(action))
        {
            if (m_input.Released(ToId(binding)))
                return true;
        }

        return false;
    }

    bool Held(Action action) const
    {
        for (auto& binding : m_actions.GetBindings(action))
        {
            if (m_input.Held(ToId(binding)))
                return true;
        }

        return false;
    }

    bool DoublePressed(Action action) const
    {
        for (auto& binding : m_actions.GetBindings(action))
        {
            if (m_input.DoublePressed(ToId(binding)))
                return true;
        }

        return false;
    }

    float Axis(Action action) const
    {
        for (auto& binding : m_actions.GetBindings(action))
        {
            return m_input.GetAxis(ToId(binding));
        }

        return 0.0f;
    }

    double GetCursorX() const
    {
        return m_input.GetCursorX();
    }

    double GetCursorY() const
    {
        return m_input.GetCursorY();
    }

private:
    int ToId(const InputBinding& binding) const
    {
        switch (binding.Type)
        {
            case InputType::KeyboardKey:
                return KEYBOARD_OFFSET + binding.Code;

            case InputType::GamepadButton:
                return GAMEPAD_OFFSET + binding.Code;

            case InputType::GamepadAxis:
                return GAMEPAD_AXIS_OFFSET + binding.Code;

            case InputType::MouseButton:
                return MOUSE_OFFSET + binding.Code;
        }

        return -1;
    }

private:
    InputSystem& m_input;
    ActionMap m_actions;

};
