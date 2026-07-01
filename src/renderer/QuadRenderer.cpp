#include "QuadRenderer.hpp"


QuadRenderer::QuadRenderer()
{
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    // float verticies[] = {
    //     -0.5f, -0.5f,
    //      0.5f, -0.5f,
    //      0.5f,  0.5f,
    //     -0.5f,  0.5f
    // };

    float verticies[] = {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        0.f, 1.f
    };

    m_shader = std::make_unique<Shader>("src/renderer/shaders/Color.shader");

    m_vertexArray = std::make_unique<VertexArray>();
    m_indexBuffer = std::make_unique<IndexBuffer>(indicies, 6);
    m_vertexBuffer = std::make_unique<VertexBuffer>(verticies, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
}


void QuadRenderer::Render(OrthographicCamera camera, glm::vec2 position, glm::vec2 size, glm::vec4 color) const
{
    Renderer renderer;

    float halfWidth = camera.Size.x * 0.5;
    float halfHeight = camera.Size.y * 0.5;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0));
    model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-camera.Pos.x, -camera.Pos.y, 0));

    glm::mat4 projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);

    glm::mat4 mvp = projection * view * model;
    
    m_shader->Bind();
    m_shader->SetUniformMat4f("u_MVP", mvp);
    m_shader->SetUniform4f("u_Color", color.x, color.y, color.z, color.w);

    renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
}
