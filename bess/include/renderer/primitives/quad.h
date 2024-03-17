#pragma once
#include "gl/utils.h"
#include "primitive.h"
namespace Bess::Renderer2D::Primitives {
class Quad : public Primitive {
  public:
    Quad();
    ~Quad();

    void draw() const override;

  private:
    std::vector<Bess::Gl::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
};

} // namespace Bess::Renderer2D::Primitives
