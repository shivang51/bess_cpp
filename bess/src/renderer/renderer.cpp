#include "renderer/renderer.h"
#include "gl/framebuffer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer/camera.h"
#include "renderer/primitives/quad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

namespace Bess::Renderer2D {

void Renderer::draw(const Gl::Vao &vao, const Gl::Ibo &ibo,
                    const Gl::Shader &shader) const {
    shader.bind();
    vao.bind();
    ibo.bind();
    glDrawElements(GL_TRIANGLES, ibo.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::quad() {
    if (!m_quad)
        m_quad = std::make_unique<Primitives::Quad>();
    m_quad->draw(m_camera->getTransform());
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1, 0.1, 1.0f);
}

void Renderer::init() {
    m_camera = std::make_unique<Camera>();
    m_camera->resize(800, 500);
    m_framebuffer = std::make_unique<Gl::FrameBuffer>(800, 500);
}

void Renderer::resize(glm::vec2 size) const {
    m_camera->resize(size.x, size.y);
    m_framebuffer->resize(size.x, size.y);
    glViewport(0, 0, size.x, size.y);
}

Camera *Renderer::getCamera() { return m_camera.get(); }

glm::vec2 Renderer::getFrameBufferSize() const {
    return m_framebuffer->getSize();
}

void Renderer::beginScene() { m_framebuffer->bind(); }
void Renderer::endScene() { m_framebuffer->unbind(); }

GLuint Renderer::getData() const { return m_framebuffer->getTexture(); }

} // namespace Bess::Renderer2D
