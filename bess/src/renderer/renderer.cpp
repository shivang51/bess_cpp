#include "renderer/renderer.h"

namespace Bess::Gl {
void Renderer::draw(const Vao &vao, const Ibo &ibo,
                    const Shader &shader) const {
    shader.bind();
    vao.bind();
    ibo.bind();
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2, 0.2, 0.2, 1.0f);
}

} // namespace Bess::Gl
