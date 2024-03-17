#pragma once

#include "gl/ibo.h"
#include "gl/shader.h"
#include "gl/vao.h"

namespace Bess::Renderer2D::Primitives {
class Primitive {
  public:
    Primitive() = default;

    ~Primitive();

    virtual void draw() const = 0;

  protected:
    Gl::Vao *m_vao;
    Gl::Ibo *m_ibo;
    Gl::Shader *m_shader;
};
} // namespace Bess::Renderer2D::Primitives
