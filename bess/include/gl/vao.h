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
    Vao(const std::vector<Vertex> &vertices);
    ~Vao();

    void bind() const;
    void unbind() const;

  private:
    GLuint m_vao_id, m_vbo_id;
};
} // namespace Bess::Gl
