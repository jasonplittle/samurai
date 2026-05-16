#include "Sprite.hpp"

#include <iostream>


Sprite::Sprite(const std::string& textureFilePath, glm::vec2 cellSize, glm::vec4 padding)
    : m_cellSize(cellSize), m_padding(padding)
{
    m_texture = std::make_unique<Texture>(textureFilePath);
}

Sprite::Sprite(const std::string& textureFilePath, glm::vec2 cellSize) 
    : Sprite(textureFilePath, cellSize, glm::vec4(0.f, 0.f, 0.f, 0.f)) 
{}

glm::vec4 Sprite::GetUV(glm::vec2 cellCoords, bool flipX) const
{
    glm::ivec2 spriteSize{ m_texture->GetWidth(), m_texture->GetHeight() };

    float x0 = (cellCoords.x * m_cellSize.x);
    float x1 = (x0 + m_cellSize.x) ;
    float y1 = cellCoords.y * m_cellSize.y;
    float y0 = y1 + m_cellSize.y;

    x0 += m_padding.x;
    x1 -= m_padding.y;
    y0 -= m_padding.z;
    y1 += m_padding.w;

    x0 /= spriteSize.x;
    x1 /= spriteSize.x;
    y0 /= spriteSize.y;
    y1 /= spriteSize.y;
    

    if (flipX) return { x1, y1, x0, y0 };
    else return { x0, y1, x1, y0 };
}

