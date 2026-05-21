#include "Game.hpp"

#include "SamuraiCharacterFactory.hpp"
#include "ForestTilesetFactory.hpp"
#include "ForestBackdropParallaxFactory.hpp"


constexpr glm::ivec2 VIRTUAL_SCEEEN = { 640, 360 };

Game::Game() 
    :    
    m_world(ForestTilesetFactory::CreateTileSet()), 
    m_background(ForestBackdropParallaxFactory::CreateBackdrop(VIRTUAL_SCEEEN.x, VIRTUAL_SCEEEN.y))
{
    m_player1 = SamuraiCharacterFactory::CreateSamuraiCharacter(glm::vec2(VIRTUAL_SCEEEN.x * 0.5, VIRTUAL_SCEEEN.y));
    m_camera =
    {
        .Pos = glm::vec2(m_player1->Body().Position.x, VIRTUAL_SCEEEN.y * 0.5),
        .Size = VIRTUAL_SCEEEN,
        .Zoom = 1
    };
}

void Game::Init()
{
    m_world.CreateDefaultWorld();
}

void Game::ReadInput(glm::ivec2 windowSize, Inputs inputs)
{
    m_player1Input.ability = inputs.space;
    m_player1Input.up = inputs.up;
    m_player1Input.down = inputs.down;
    m_player1Input.left = inputs.left;
    m_player1Input.right = inputs.right;


    glm::vec2 mouseWorldPos = 
    {
        (inputs.mousePos.x / (windowSize.x / VIRTUAL_SCEEEN.x)) - (m_camera.Size.x * 0.5) + m_camera.Pos.x, 
        (((windowSize.y - inputs.mousePos.y) / (windowSize.y / VIRTUAL_SCEEEN.y)) - (m_camera.Size.y * 0.5) + m_camera.Pos.y) 
    };

    if (inputs.lMouse)
    {
        m_world.ShowTile(true, mouseWorldPos.x, mouseWorldPos.y);
    }
    if (inputs.rMouse)
    {
        m_world.ShowTile(false, mouseWorldPos.x, mouseWorldPos.y);
    }
}

void Game::Update(float dt)
{
    m_playerController.Update(dt, *m_player1, m_player1Input);
    m_physics.UpdateBody(m_player1->Body(), m_world, dt);
    m_player1->Update(dt);

    m_camera.Pos.x = m_player1->Body().Position.x;
}

void Game::Render()
{
    m_background.RenderLayers(m_renderer, m_camera);
    m_world.DrawTiles(m_renderer, m_camera);

    m_renderer.Render(
        m_player1->Animator().GetCurrentSprite(),
        glm::ivec2(m_player1->Animator().GetCurrentFrame(), 0), 
        !m_player1->IsFacingRight(),
        m_camera,
        m_player1->Body().Position - m_player1->Animator().GetFrameCenterOffset(),
        m_player1->Animator().GetFrameSize()
    );
}