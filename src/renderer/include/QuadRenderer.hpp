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


class QuadRenderer
{
public:
    QuadRenderer();

    void Render(OrthographicCamera camera, glm::vec2 position, glm::vec2 size, glm::vec4 color) const;

private:
    std::unique_ptr<Shader> m_shader;

    std::unique_ptr<VertexArray> m_vertexArray;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};