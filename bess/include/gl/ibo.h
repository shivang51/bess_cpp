#pragma once

#include "glad/glad.h"
#include <vector>
namespace Bess::Gl {
class Ibo {
  public:
    Ibo() = default;
    Ibo(const std::vector<GLuint> &indices);
    ~Ibo();
    void bind() const;
    void unbind() const;

  private:
    GLuint m_ibo_id;
};
} // namespace Bess::Gl
