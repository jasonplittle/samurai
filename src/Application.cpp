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
#include "CharacterAnimator.hpp"
#include "SamuraiAnimationFactory.hpp"
#include "ExecutionerAnimationFactory.hpp"
#include "SpriteRenderer.hpp"

#include "BackgroundParallax.hpp"
#include "ForestBackdropParallaxFactory.hpp"

#include "World.hpp"
#include "ForestTilesetFactory.hpp"


// constexpr glm::ivec2 VIRTUAL_SCEEEN = { 320, 180 };
constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };
// constexpr glm::ivec2 VIRTUAL_SCEEEN = { 1280, 720 };
constexpr glm::ivec2 REAL_SCEEEN = { 1280, 720 };
constexpr glm::vec2 SCREEN_FACTOR = { REAL_SCEEEN.x / VIRTUAL_SCEEEN.x, REAL_SCEEEN.y / VIRTUAL_SCEEEN.y };


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

    Character player(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y), glm::vec2(32, 32));
    PlayerController playerController(player);

    Character player2(glm::vec2(VIRTUAL_SCEEEN.x * 0.5 + 50, VIRTUAL_SCEEEN.y), glm::vec2(48, 48));
    PlayerController player2Controller(player2);
    
    

    SpriteRenderer spriteRenderer;

    BackgroundParallax backdrop(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y));

    World world(ForestTilesetFactory::CreateTileSet());
    world.CreateDefaultWorld();

    InputState inputState;
    InputState inputState2;

    OrthographicCamera camera
    {
        .Pos = glm::vec2(player.GetPosition().x, VIRTUAL_SCEEEN.y * 0.5),
        // .Pos = glm::vec2(VIRTUAL_SCEEEN.x * 0, VIRTUAL_SCEEEN.y * 0),
        .Size = VIRTUAL_SCEEEN,
        .Zoom = 1
    };

    PhysicsSystem physics;
    
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
        inputState.up = Input::Instance().IsKeyPressed(window, GLFW_KEY_UP);
        inputState.down = Input::Instance().IsKeyPressed(window, GLFW_KEY_DOWN);
        inputState.ability = Input::Instance().IsKeyPressed(window, GLFW_KEY_SPACE);

        inputState2.left = Input::Instance().IsKeyPressed(window, GLFW_KEY_A);
        inputState2.right = Input::Instance().IsKeyPressed(window, GLFW_KEY_D);
        inputState2.up = Input::Instance().IsKeyPressed(window, GLFW_KEY_W);
        inputState2.down = Input::Instance().IsKeyPressed(window, GLFW_KEY_S);
        inputState2.ability = Input::Instance().IsKeyPressed(window, GLFW_KEY_F);

        bool lMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_LEFT);
        bool rMouse = Input::Instance().IsMousePressed(window, GLFW_MOUSE_BUTTON_RIGHT);
        glm::vec2 mouseScreenPos = Input::Instance().GetCursorPos(window);
        glm::vec2 mouseWorldPos = 
        {
            (mouseScreenPos.x / SCREEN_FACTOR.x) - (camera.Size.x * 0.5) + camera.Pos.x, 
            (((REAL_SCEEEN.y - mouseScreenPos.y) / SCREEN_FACTOR.y) - (camera.Size.y * 0.5) + camera.Pos.y) 
        };

        if (lMouse)
        {
            // std::cout << "left: " << (REAL_SCEEEN.y - mouseScreenPos.y) << ", " << ((REAL_SCEEEN.y - mouseScreenPos.y) / SCREEN_FACTOR.y) << ", " << mouseWorldPos.y << ", " << camera.Pos.y << std::endl;
            world.ShowTile(true, mouseWorldPos.x, mouseWorldPos.y);
        }
        if (rMouse)
        {
            // std::cout << "right: " << cPos.x << ", " << cPos.y << std::endl;
            world.ShowTile(false, mouseWorldPos.x, mouseWorldPos.y);
        }

        player2Controller.Update(dt, inputState2);
        physics.UpdateBody(player2.GetBody(), world, dt);
        player2.Update(dt);

        playerController.Update(dt, inputState);
        physics.UpdateBody(player.GetBody(), world, dt);
        player.Update(dt);

        


        camera.Pos.x = player.GetPosition().x;

        backdrop.RenderLayers(spriteRenderer, camera);

        world.DrawTiles(spriteRenderer, camera);

        spriteRenderer.Render(
            player2Animation.GetCurrentSprite(),
            glm::ivec2(player2Animation.GetCurrentFrame(), 0), 
            !player2.IsFacingRight(),
            camera,
            player2.GetPosition() - player2Animation.GetFrameCenterOffset(),
            player2Animation.GetFrameSize()
        );

        spriteRenderer.Render(
            playerAnimation.GetCurrentSprite(),
            glm::ivec2(playerAnimation.GetCurrentFrame(), 0), 
            !player.IsFacingRight(),
            camera,
            player.GetPosition() - playerAnimation.GetFrameCenterOffset(),
            playerAnimation.GetFrameSize()
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
