#pragma once

#include <glm/glm.hpp>


struct OrthographicCamera
{
    glm::vec2 Pos;
    glm::vec2 Size;
    int Zoom;
};
