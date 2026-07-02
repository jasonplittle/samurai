#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "Renderer.hpp"

#include "GameInput.hpp"
#include "Game.hpp"


ActionMap getKeyBinds()
{
    ActionMap actionMap;

    actionMap.Bind(Action::MoveX, { InputType::GamepadAxis, GLFW_GAMEPAD_AXIS_LEFT_X });

    actionMap.Bind(Action::MoveLeft, { InputType::KeyboardKey, GLFW_KEY_A });
    actionMap.Bind(Action::MoveLeft, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_DPAD_LEFT });

    actionMap.Bind(Action::MoveRight, { InputType::KeyboardKey, GLFW_KEY_D });
    actionMap.Bind(Action::MoveRight, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT });

    actionMap.Bind(Action::Jump, { InputType::KeyboardKey, GLFW_KEY_W });
    actionMap.Bind(Action::Jump, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_A });

    actionMap.Bind(Action::Down, { InputType::KeyboardKey, GLFW_KEY_S });
    actionMap.Bind(Action::Down, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_DPAD_DOWN });
    actionMap.Bind(Action::Down, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER });

    actionMap.Bind(Action::Primary, { InputType::KeyboardKey, GLFW_KEY_SPACE });
    actionMap.Bind(Action::Primary, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER });

    actionMap.Bind(Action::Secondary, { InputType::KeyboardKey, GLFW_KEY_F });
    actionMap.Bind(Action::Secondary, { InputType::GamepadAxis, GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER });

    actionMap.Bind(Action::Throw, { InputType::KeyboardKey, GLFW_KEY_E });
    actionMap.Bind(Action::Throw, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_Y });

    actionMap.Bind(Action::Ultimate, { InputType::KeyboardKey, GLFW_KEY_R });
    actionMap.Bind(Action::Ultimate, { InputType::GamepadAxis, GLFW_GAMEPAD_AXIS_LEFT_TRIGGER });

    actionMap.Bind(Action::Heal, { InputType::KeyboardKey, GLFW_KEY_H });
    actionMap.Bind(Action::Heal, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_X });

    actionMap.Bind(Action::Slow, { InputType::KeyboardKey, GLFW_KEY_LEFT_SHIFT });
    actionMap.Bind(Action::Dash, { InputType::GamepadButton, GLFW_GAMEPAD_BUTTON_B });

    actionMap.Bind(Action::PlaceTile, { InputType::MouseButton, GLFW_MOUSE_BUTTON_LEFT });
    actionMap.Bind(Action::RemoveTile, { InputType::MouseButton, GLFW_MOUSE_BUTTON_RIGHT });
    actionMap.Bind(Action::PlaceMob, { InputType::KeyboardKey, GLFW_KEY_M });
    actionMap.Bind(Action::PlaceProp, { InputType::KeyboardKey, GLFW_KEY_T });

    return actionMap;
}


void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mods)
{
    auto* input = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));

    if (!input) return;

    if (action == GLFW_PRESS)
    {
        input->OnKeyPressed(key + KEYBOARD_OFFSET);
    }
    else if (action == GLFW_RELEASE)
    {
        input->OnKeyReleased(key + KEYBOARD_OFFSET);
    }
}


void mouseButtonCallback(GLFWwindow* window,
                         int button,
                         int action,
                         int mods)
{
    InputSystem* input = static_cast<InputSystem*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS)
    {
        input->OnKeyPressed(button + MOUSE_OFFSET);
    }
    else if (action == GLFW_RELEASE)
    {
        input->OnKeyReleased(button + MOUSE_OFFSET);
    }
}


void readCursor(GLFWwindow* window, InputSystem* input)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    input->SetCursor(x, y);
}


void readGamepad(GLFWgamepadstate* pad, InputSystem* input)
{
    if (!glfwGetGamepadState(GLFW_JOYSTICK_1, pad))
        return;
    
    for (int i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; ++i)
    {
        if (pad->buttons[i] == GLFW_PRESS)
        {
            input->OnKeyPressed(i + GAMEPAD_OFFSET);
        }
        else if (pad->buttons[i] == GLFW_RELEASE)
        {
            input->OnKeyReleased(i + GAMEPAD_OFFSET);
        }
    }

    for (int i = 0; i <= GLFW_GAMEPAD_AXIS_LAST; ++i)
    {
        float val = pad->axes[i];

        if (i == GLFW_GAMEPAD_AXIS_LEFT_TRIGGER || i == GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER)
        {
            val = (val + 1.0f) * 0.5f;
            if (val < 0.05f) 
                val = 0.0f;
        }
        else
        {
            if (std::abs(val) < 0.15f)
                val = 0.0f;
        }

        input->UpdateAxis(i + GAMEPAD_AXIS_OFFSET, val);
    }
}


void setIcon(GLFWwindow* window, GLFWimage* icon)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load("resources/icon.png", &width, &height, &channels, 4);

    if (!pixels)
    {
        std::cout << "Failed to load icon image" << std::endl;
        return;
    }
    
    icon->width = width;
    icon->height = height;
    icon->pixels = pixels;

    glfwSetWindowIcon(window, 1, icon);

    stbi_image_free(pixels);
}


int main()
{
    std::cout << "Starting Application..." << std::endl;

    GLFWwindow* window;
    GLFWimage icon;
    GLFWgamepadstate pad;
    Renderer renderer;
    int windowWidth, windowHeight;
    float lastTime;
    float currentTime;
    float dt;
    InputSystem input;
    GameInput gameInput(input, getKeyBinds());


    if (!glfwInit())
    {
        std::cout << "Failed to init glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Samurai", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init glew" << std::endl;
        return -1;
    }
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    glfwSetWindowUserPointer(window, &input);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    setIcon(window, &icon);
    
    renderer.EnableBlending();


    Game game(gameInput);
    game.Init();
    lastTime = glfwGetTime();
    
    
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        renderer.Clear();
        renderer.Viewport(windowWidth, windowHeight);

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        input.BeginFrame(dt);
        
        glfwPollEvents();

        readGamepad(&pad, &input);
        readCursor(window, &input);
        
        game.Update(dt, windowWidth, windowHeight);
        game.Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
