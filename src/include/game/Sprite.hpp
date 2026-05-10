#pragma once

#include <memory>

#include "Texture.hpp"

#include <glm/glm.hpp>


class Sprite
{
public:
    Sprite(const std::string& textureFilePath, glm::vec2 spriteTextureSize, int atlasPosition);

    const Texture& GetTexture() const { return *m_texture; }

    glm::vec4 GetAtlasCoords(bool flipX) const;
    void SetAtlasPosition(int atlasPosition) { m_atlasPosition = atlasPosition; }
    glm::vec4 GetColor() const { return m_color; }
    void SetColor(glm::vec4 color) { m_color = color; }
    
private:
    std::unique_ptr<Texture> m_texture;
    int m_atlasPosition;
    glm::vec2 m_spriteSize;
    glm::vec4 m_color = { 1.0, 1.0, 1.0, 1.0 };

    glm::vec2 m_spriteTextureSize;
};
