#pragma once

#include "Props.hpp"


class ForestPropsetFactory
{
public:
    static PropSet CreatePropset()
    {
        PropSet propSet;
        
        propSet.Set[PropId::Tree1] = 
        {
            .Size = glm::vec2(120, 160),
            .Sprite = std::make_unique<Sprite>("resources/props/Tree1.png", glm::vec2(120, 160))
        };

        propSet.Set[PropId::Tree2] = 
        {
            .Size = glm::vec2(120, 160),
            .Sprite = std::make_unique<Sprite>("resources/props/Tree2.png", glm::vec2(120, 160))
        };

        propSet.Set[PropId::Tree3] = 
        {
            .Size = glm::vec2(130, 160),
            .Sprite = std::make_unique<Sprite>("resources/props/Tree3.png", glm::vec2(130, 160))
        };

        return propSet;
    }
};