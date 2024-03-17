#pragma once
extern "C" {
#include "glad/glad.h"
}

#include "ibo.h"

#include "vertex.h"

#include <vector>
namespace Bess::Gl {
class Vao {
  public:
    Vao() = default;
    Vao(const std::vector<Vertex> &vertices);
    ~Vao();

    void bind() const;
    void unbind() const;
    GLuint getId() const;

  private:
    std::vector<Vertex> m_vertices;
    GLuint m_vao_id = -1, m_vbo_id = -1;
};
} // namespace Bess::Gl
