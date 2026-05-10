#include "Sprite.hpp"


Sprite::Sprite(const std::string& textureFilePath, glm::ivec2 spriteTextureSize, int atlasPosition)
    : m_spriteTextureSize(spriteTextureSize), m_atlasPosition(atlasPosition) 
{
    m_texture = std::make_unique<Texture>(textureFilePath);

    glm::ivec2 atlasSize{ m_texture->GetWidth(), m_texture->GetHeight() };
    glm::ivec2 pixelSize = { 1.0f / atlasSize.x, 1.0f / atlasSize.y };
    glm::ivec2 atlasPadding = {pixelSize.x * 0.25f, pixelSize.y * 0.25f };
    glm::ivec2 spriteSizeNormalised = { spriteTextureSize.x * pixelSize.x, spriteTextureSize.y * pixelSize.y };

    float x0 = 0.0f;
    float x1 = spriteSizeNormalised.x;
    float y0 = 1.0f - spriteSizeNormalised.y;
    float y1 = 1.0f;
}

glm::vec4 Sprite::GetAtlasCoords(bool flipX) const
{
    IVec2 atlasSize{ m_texture->GetWidth(), m_texture->GetHeight() };
    Vec2 pixelSize = { 1.0f / atlasSize.x, 1.0f / atlasSize.y };
    Vec2 atlasPadding = {pixelSize.x * 0.25f, pixelSize.y * 0.25f };

    float x0 = m_spriteTextureSize.x * m_atlasPosition + 2 * m_atlasPosition;
    float x1 = x0 + m_spriteTextureSize.x;
    float y0 = m_spriteTextureSize.y * m_atlasPosition + 2 * m_atlasPosition;
    float y1 = y0 + m_spriteTextureSize.y;

    x0 *= pixelSize.x;
    x1 *= pixelSize.x;
    y0 *= pixelSize.y;
    y1 *= pixelSize.y;

    y0 = 1 - y0;
    y1 = 1 - y1;

    x0 += atlasPadding.x;
    x1 += -atlasPadding.x;
    y0 += -atlasPadding.y;
    y1 += atlasPadding.y;

    if (flipX) return { x1, y1, x0, y0 };
    else return { x0, y1, x1, y0 };
}

