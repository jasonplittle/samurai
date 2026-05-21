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

struct OrthographicCamera
{
    glm::vec2 Pos;
    glm::vec2 Size;
    int Zoom;
};

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
    ) const;

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};