#pragma once

#include "gl/ibo.h"
#include "gl/shader.h"
#include "gl/vao.h"
namespace Bess::Gl {
class Renderer {
  public:
    Renderer() = default;
    void draw(const Vao &vao, const Ibo &ibo, const Shader &shader) const;
    void clear() const;
};

} // namespace Bess::Gl
