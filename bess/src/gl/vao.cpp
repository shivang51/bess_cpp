#include "gl/vao.h"
#include <cstddef>
#include <iostream>
#include <vector>

#include "gl/gl_wrapper.h"
#include "gl/vertex.h"
#include "window.h"

namespace Bess::Gl {

Vao::Vao(const std::vector<Vertex> &vertices) {
    std::cout << "Vertex: " << sizeof(Vertex) * vertices.size() << std::endl;

    // m_vertices = vertices;
    GL_CHECK(glGenVertexArrays(1, &m_vao_id));
    std::cout << "create vao with id " << m_vao_id << std::endl;
    GL_CHECK(glBindVertexArray(m_vao_id));

    GL_CHECK(glGenBuffers(1, &m_vbo_id));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                          vertices.data(), GL_STATIC_DRAW));

    // GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *
    // m_vertices.size(),
    //                       m_vertices.data(), GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                   (const void *)offsetof(Vertex, position)));

    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                   (const void *)offsetof(Vertex, color)));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));
}

Vao::~Vao() {
    std::cout << "deleting vao " << m_vao_id << std::endl;
    glDeleteBuffers(1, &m_vbo_id);
    glDeleteVertexArrays(1, &m_vao_id);
}

GLuint Vao::getId() const { return m_vao_id; }

void Vao::bind() const {
    // std::cout << "Binding VAO " << m_vao_id << std::endl;
    GL_CHECK(glBindVertexArray(m_vao_id));
}
void Vao::unbind() const { glBindVertexArray(0); }

} // namespace Bess::Gl
