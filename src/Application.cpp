#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Renderer.hpp"
#include "Input.hpp"
#include "Game.hpp"


int main()
{
    std::cout << "Starting Application..." << std::endl;

    GLFWwindow* window;

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

    if (glewInit() != GLEW_OK) return -1;
    std::cout << glGetString(GL_VERSION) << std::endl;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    int windowWidth, windowHeight;

    Renderer renderer;
    renderer.EnableBlending();

    float lastTime = glfwGetTime();
    float currentTime;
    float dt;

    Inputs inputs;

    Game game;
    game.Init();
    
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        renderer.Clear();
        renderer.Viewport(windowWidth, windowHeight);

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        inputs.left = Input::Instance().IsKeyPressed(window, GLFW_KEY_LEFT);
        inputs.right = Input::Instance().IsKeyPressed(window, GLFW_KEY_RIGHT);
        inputs.up = Input::Instance().IsKeyPressed(window, GLFW_KEY_UP);
        inputs.down = Input::Instance().IsKeyPressed(window, GLFW_KEY_DOWN);
        inputs.space = Input::Instance().IsKeyPressed(window, GLFW_KEY_SPACE);

        // inputs.a = Input::Instance().IsKeyPressed(window, GLFW_KEY_A);
        // inputs.d = Input::Instance().IsKeyPressed(window, GLFW_KEY_D);
        // inputs.w = Input::Instance().IsKeyPressed(window, GLFW_KEY_W);
        // inputs.s = Input::Instance().IsKeyPressed(window, GLFW_KEY_S);
        // inputs.f = Input::Instance().IsKeyPressed(window, GLFW_KEY_F);

        inputs.t = Input::Instance().IsKeyPressed(window, GLFW_KEY_T);
        inputs.m = Input::Instance().IsKeyPressed(window, GLFW_KEY_M);

        inputs.lMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_LEFT);
        inputs.rMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_RIGHT);
        inputs.mousePos = Input::Instance().GetCursorPos(window);
        
        game.ReadInput(glm::vec2(windowWidth, windowHeight), inputs);
        game.Update(dt);
        game.Render();

        glfwSwapBuffers(window);
		glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
