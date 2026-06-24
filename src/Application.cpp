#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "Renderer.hpp"
#include "Input.hpp"
#include "Game.hpp"

#include "GameInput.hpp"


ActionMap getKeyBinds()
{
    ActionMap actionMap;

    actionMap.Bind(
        Action::MoveLeft,
        GLFW_KEY_A);

    actionMap.Bind(
        Action::MoveRight,
        GLFW_KEY_D);

    actionMap.Bind(
        Action::Jump,
        GLFW_KEY_W);

    actionMap.Bind(
        Action::Down,
        GLFW_KEY_S);

    actionMap.Bind(
        Action::Primary,
        GLFW_KEY_SPACE);

    actionMap.Bind(
        Action::Secondary,
        GLFW_KEY_F);

    actionMap.Bind(
        Action::Ultimate,
        GLFW_KEY_R);

    actionMap.Bind(
        Action::Slow,
        GLFW_KEY_LEFT_SHIFT);

    return actionMap;
}


void KeyCallback(
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
        input->OnKeyPressed(key);
    }
    else if (action == GLFW_RELEASE)
    {
        input->OnKeyReleased(key);
    }
}

void setIcon(GLFWwindow* window, GLFWimage* icon)
{
    int width, height, channels;
    unsigned char* pixels = stbi_load("resources/icon.png", &width, &height, &channels, 4);

    if (pixels)
    {
        icon->width = width;
        icon->height = height;
        icon->pixels = pixels;

        glfwSetWindowIcon(window, 1, icon);

        stbi_image_free(pixels);
    }
}


int main()
{
    std::cout << "Starting Application..." << std::endl;

    GLFWwindow* window;
    GLFWimage icon;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Samurai", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    setIcon(window, &icon);

    if (glewInit() != GLEW_OK) return -1;
    std::cout << glGetString(GL_VERSION) << std::endl;

    int windowWidth, windowHeight;

    Renderer renderer;
    renderer.EnableBlending();

    float lastTime = glfwGetTime();
    float currentTime;
    float dt;

    Inputs inputs;

    InputSystem input;
    glfwSetWindowUserPointer(window, &input);
    glfwSetKeyCallback(window, KeyCallback);

    GameInput gameInput(input, getKeyBinds());

    Game game(gameInput);
    game.Init();
    
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

        inputs.t = Input::Instance().IsKeyPressed(window, GLFW_KEY_T);
        inputs.m = Input::Instance().IsKeyPressed(window, GLFW_KEY_M);
        inputs.lMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_LEFT);
        inputs.rMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_RIGHT);
        inputs.mousePos = Input::Instance().GetCursorPos(window);
        
        game.ReadInput(glm::vec2(windowWidth, windowHeight), inputs);
        game.Update(dt);
        game.Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
