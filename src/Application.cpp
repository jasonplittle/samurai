#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include "Renderer.hpp"
#include "Input.hpp"
#include "PlayerController.hpp"
#include "Character.hpp"
#include "CharacterAnimation.hpp"
#include "SamuraiAnimationFactory.hpp"
#include "SpriteRenderer.hpp"

#include "BackgroundParallax.hpp"
#include "ForestBackdropParallaxFactory.hpp"

#include "World.hpp"
#include "ForestTilesetFactory.hpp"

constexpr glm::ivec2 REAL_SCEEEN = { 1280, 720 };
// constexpr glm::ivec2 VIRTUAL_SCEEEN = { 320, 180 };
constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };

constexpr glm::vec2 SCEEEN_FACTOR = { REAL_SCEEEN.x / VIRTUAL_SCEEEN.x, REAL_SCEEEN.y / VIRTUAL_SCEEEN.y };


// constexpr glm::vec2 VIRTUAL_SCEEEN = { 640.0f, 360.0f };

int main()
{
    std::cout << "Starting Application..." << std::endl;

    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(REAL_SCEEEN.x, REAL_SCEEEN.y, "Samurai", nullptr, nullptr);

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
    PlayerController playerController(player);

    CharacterAnimation playerAnimation(player.GetState(), SamuraiAnimationFactory::CreateSamuraiAnimations());

    SpriteRenderer spriteRenderer;

    BackgroundParallax backdrop(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y));

    World world(ForestTilesetFactory::CreateTileSet());

    InputState inputState;

    OrthographicCamera camera;
    camera.Pos.y = 0;
    camera.Zoom = 1;
    camera.Size = VIRTUAL_SCEEEN;
    
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        renderer.Clear();
        renderer.Viewport(windowWidth, windowHeight);

        // game.GetInput
        // game.Update
        // game.render

        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        inputState.left = Input::Instance().IsKeyPressed(window, GLFW_KEY_LEFT);
        inputState.right = Input::Instance().IsKeyPressed(window, GLFW_KEY_RIGHT);
        inputState.jump = Input::Instance().IsKeyPressed(window, GLFW_KEY_UP);
        inputState.attack = Input::Instance().IsKeyPressed(window, GLFW_KEY_SPACE);

        bool lMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_LEFT);
        bool rMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_RIGHT);
        glm::vec2 cPos = Input::Instance().GetCursorPos(window);
        glm::vec2 cWPos = {cPos.x / SCEEEN_FACTOR.x, cPos.y / SCEEEN_FACTOR.x };

        if (lMouse)
        {
            // std::cout << "left: " << cPos.x << ", " << cPos.y << std::endl;
            world.ShowTile(true, cWPos.x, cWPos.y);
        }
        if (rMouse)
        {
            // std::cout << "right: " << cPos.x << ", " << cPos.y << std::endl;
            world.ShowTile(false, cWPos.x, cWPos.y);
        }

        playerController.Update(dt, inputState);
        playerAnimation.Update(dt, player.GetState());
        player.Update(dt, playerAnimation.IsFinished());

        camera.Pos.x = player.GetPosition().x;

        backdrop.RenderLayers(spriteRenderer, camera);

        world.DrawTiles(spriteRenderer, camera);

        spriteRenderer.Render(
            playerAnimation.GetCurrentSprite(),
            glm::ivec2(playerAnimation.GetCurrentFrame(), 0), 
            !player.IsFacingRight(),
            camera,
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
