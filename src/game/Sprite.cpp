#include "Sprite.hpp"


Sprite::Sprite(const std::string& textureFilePath, glm::vec2 cellSize)
    : m_cellSize(cellSize) 
{
    m_texture = std::make_unique<Texture>(textureFilePath);
}

glm::vec4 Sprite::GetUV(glm::vec2 cellCoords, bool flipX) const
{
    glm::ivec2 spriteSize{ m_texture->GetWidth(), m_texture->GetHeight() };

    // Vec2 pixelSize = { 1.0f / spriteSize.x, 1.0f / spriteSize.y };

    float x0 = cellCoords.x * m_cellSize.x;
    float x1 = x0 + m_cellSize.x;
    float y1 = cellCoords.y * m_cellSize.y;
    float y0 = y1 + m_cellSize.y;
    

    if (flipX) return { x1, y1, x0, y0 };
    else return { x0, y1, x1, y0 };
}

