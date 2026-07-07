#pragma once

#include "MobManager.hpp"
#include "World.hpp"
#include "Props.hpp"
#include "GameInput.hpp"
#include "SpriteRenderer.hpp"
#include "LightManager.hpp"
#include "IGameplayContext.hpp"


class WorldEditor
{
public:
    void Update(int windowWidth, 
                int windowHeight, 
                OrthographicCamera camera, 
                GameInput& input, 
                Props& props, 
                World& world, 
                MobManager& mobs,
                LightManager& lights,
                IGameplayContext& context)
    {
        glm::vec2 mouseWorldPos = 
        {
            (input.GetCursorX() / (windowWidth / camera.Size.x)) - (camera.Size.x * 0.5) + camera.Pos.x, 
            (((windowHeight - input.GetCursorY()) / (windowHeight / camera.Size.y)) - (camera.Size.y * 0.5) + camera.Pos.y) 
        };

        if (input.Pressed(Action::PlaceTile))
        {
            world.ShowTile(true, mouseWorldPos.x, mouseWorldPos.y);
        }

        if (input.Pressed(Action::RemoveTile))
        {
            world.ShowTile(false, mouseWorldPos.x, mouseWorldPos.y);
        }

        if (input.Pressed(Action::PlaceMob))
        {
            mobs.AddMob(mouseWorldPos, context);
        }

        if (input.Pressed(Action::PlaceProp))
        {
            props.AddProp(mouseWorldPos.x, world);
        }

        if (input.Pressed(Action::PlaceLight))
        {
            Light light;
            light.Position = mouseWorldPos;
            lights.Add(light);
        }
    }
};
