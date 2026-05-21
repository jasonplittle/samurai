#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Texture.hpp"


class Sprite
{
public:
    Sprite(const std::string& textureFilePath, glm::vec2 cellSize, glm::vec4 padding);
    Sprite(const std::string& textureFilePath, glm::vec2 cellSize);

    const Texture& GetTexture() const { return *m_texture; }
    glm::vec4 GetUV(glm::vec2 cellCoords, bool flipX) const;
    
private:
    std::unique_ptr<Texture> m_texture;
    glm::vec2 m_cellSize;
    glm::vec4 m_padding;
};
