#include "gl/vao.h"
#include <cstddef>
#include <vector>

namespace Bess::Gl {

Vao::Vao(const std::vector<Vertex> &vertices) {
    glGenVertexArrays(1, &m_vao_id);
    glBindVertexArray(m_vao_id);

    glGenBuffers(1, &m_vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const void *)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const void *)offsetof(Vertex, color));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Vao::~Vao() {
    glDeleteBuffers(1, &m_vbo_id);
    glDeleteVertexArrays(1, &m_vao_id);
}

void Vao::bind() const { glBindVertexArray(m_vao_id); }
void Vao::unbind() const { glBindVertexArray(0); }

} // namespace Bess::Gl
