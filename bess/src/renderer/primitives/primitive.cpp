#include "renderer/primitives/primitive.h"
#include <iostream>

#include "gl/gl_wrapper.h"

namespace Bess::Renderer2D::Primitives {

Primitive::~Primitive() {
    if (m_vao)
        delete m_vao;
    if (m_ibo)
        delete m_ibo;
    if (m_shader)
        delete m_shader;
}

} // namespace Bess::Renderer2D::Primitives
