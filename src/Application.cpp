#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "Renderer.hpp"
#include "Input.hpp"
// #include "PlayerController.hpp"

#include "Character.hpp"
#include "CharacterAnimation.hpp"
#include "SamuraiAnimationFactory.hpp"
#include "SpriteRenderer.hpp"


constexpr glm::vec2 VIRTUAL_SCEEEN = { 1280.0f, 720.0f };


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

    Character player;
    // PlayerController playerController(player);

    CharacterAnimation playerAnimation(player.GetState(), SamuraiAnimationFactory::CreateSamuraiAnimations());

    SpriteRenderer spriteRenderer;


    
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        renderer.Clear();
        renderer.Viewport(windowWidth, windowHeight);

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;


        // if (Input::Instance().IsKeyPressed(window, GLFW_KEY_LEFT)) 
        //     playerController.MoveLeft();
    
        // if (Input::Instance().IsKeyPressed(window, GLFW_KEY_RIGHT));
        //     playerController.MoveRight();

        // if (Input::Instance().IsKeyPressed(window, GLFW_KEY_DOWN));
        //     playerController.MoveDown();

        // if (Input::Instance().IsKeyPressed(window, GLFW_KEY_UP))
        //     playerController.Jump();

        // if (Input::Instance().IsKeyPressed(window, GLFW_KEY_SPACE))
        //     playerController.Attack();
        

        // playerController.Update(dt);
        playerAnimation.Update(dt, player.GetState());

        spriteRenderer.Render(
            playerAnimation.GetCurrentSprite(),
            glm::ivec2(playerAnimation.GetCurrentFrame(), 0), 
            player.IsFacingRight(),
            player.GetPosition(),
            VIRTUAL_SCEEEN,
            player.GetPosition(),
            player.GetSize()
        );

        glfwSwapBuffers(window);
		glfwPollEvents();
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
