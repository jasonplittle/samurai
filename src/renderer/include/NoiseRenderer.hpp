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


class NoiseRenderer
{
public:
    NoiseRenderer();

    void Render(
        const Sprite& sprite, 
        OrthographicCamera camera,
        glm::vec2 modelPos, 
        glm::vec2 modelSize,
        glm::vec2 scale,
        glm::vec2 offset,
        glm::vec4 color
    ) const;

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};