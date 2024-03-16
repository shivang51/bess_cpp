#include "gl/ibo.h"

namespace Bess::Gl {
Ibo::Ibo(const std::vector<GLuint> &indices) {
    m_size = indices.size();
    glGenBuffers(1, &m_ibo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);
}

Ibo::~Ibo() { glDeleteBuffers(1, &m_ibo_id); }

void Ibo::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id); }
void Ibo::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

GLuint Ibo::size() const { return m_size; }

} // namespace Bess::Gl
