#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "Sprite.hpp"
#include "Camera.hpp"


class SpriteRenderer
{
public:
    SpriteRenderer();

    void Render(
        const Sprite& sprite, 
        glm::vec2 spriteCellCoords, 
        bool flipX,
        OrthographicCamera camera,
        glm::vec2 modelPos, 
        glm::vec2 modelSize
    ) const
    {
        Render(sprite, spriteCellCoords, flipX, camera, modelPos, modelSize, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    void Render(
        const Sprite& sprite, 
        glm::vec2 spriteCellCoords, 
        bool flipX,
        OrthographicCamera camera,
        glm::vec2 modelPos, 
        glm::vec2 modelSize,
        float opacity
    ) const
    {
        Render(sprite, spriteCellCoords, flipX, camera, modelPos, modelSize, glm::vec4(1.0f, 1.0f, 1.0f, opacity));
    }

    void Render(
        const Sprite& sprite, 
        glm::vec2 spriteCellCoords, 
        bool flipX,
        OrthographicCamera camera,
        glm::vec2 modelPos, 
        glm::vec2 modelSize,
        glm::vec4 color
    ) const;

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};