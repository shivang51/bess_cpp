#include "renderer/primitives/quad.h"
#include "gl/gl_wrapper.h"
#include "gl/utils.h"
#include "gl/vao.h"
#include "glm/glm.hpp"
#include "renderer/primitives/primitive.h"
#include <iostream>

namespace Bess::Renderer2D::Primitives {

Quad::Quad() {
    m_vertices = {
        Bess::Gl::Utils::createVertex(0.0f, 0.0f),
        Bess::Gl::Utils::createVertex(-0.5f, 0.f),
        Bess::Gl::Utils::createVertex(0.f, 0.5f),
        Bess::Gl::Utils::createVertex(-0.5f, 0.5f),
    };

    m_indices = {0, 1, 2, 2, 3, 1};

    m_vao = new Gl::Vao(m_vertices);
    m_ibo = new Gl::Ibo(m_indices);
    m_shader = new Gl::Shader("bess/src/shaders/first_vert.glsl",
                              "bess/src/shaders/first_frag.glsl");
}

Quad::~Quad() {}

void Quad::draw(const glm::mat4 &mvp) const {
    m_vao->bind();
    m_ibo->bind();
    m_shader->bind();
    glm::vec4 color(0.9f, 0.6f, 0.4f, 1.0f);
    m_shader->setUniformVec4("u_color", color);
    m_shader->setUniformMat4("u_mvp", mvp);
    GL_CHECK(
        glDrawElements(GL_TRIANGLES, m_ibo->size(), GL_UNSIGNED_INT, nullptr));
}

} // namespace Bess::Renderer2D::Primitives
