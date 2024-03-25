#include "renderer/renderer.h"
#include "fwd.hpp"
#include "gl/framebuffer.h"
#include "gl/gl_wrapper.h"
#include "renderer/camera.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace Bess::Renderer2D {

const size_t MAX_QUADS = 250;

void Renderer::init() {
    m_shader = std::make_unique<Gl::Shader>("bess/src/shaders/first_vert.glsl",
                                            "bess/src/shaders/first_frag.glsl");
    m_vao = std::make_unique<Gl::Vao>(MAX_QUADS * 4, MAX_QUADS * 6);
    m_camera = std::make_unique<Camera>();
    m_camera->resize(800, 500);
    m_framebuffer = std::make_unique<Gl::FrameBuffer>(800, 500);
}

void Renderer::createQuad(const glm::vec2 &pos, const glm::vec2 &size,
                          const glm::vec3 &color) {
    std::vector<Gl::Vertex> vertices(4);
    vertices[0].position = {pos.x, pos.y, 0.0f};
    vertices[1].position = {pos.x, pos.y - size.y, 0.0f};
    vertices[2].position = {pos.x + size.x, pos.y - size.y, 0.0f};
    vertices[3].position = {pos.x + size.x, pos.y, 0.0f};
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
    m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
}

void Renderer::quad(const glm::vec2 &pos, const glm::vec2 &size,
                    const glm::vec3 &color) {
    if (m_vertices.size() >= (MAX_QUADS - 1) * 4) {
        flush();
    }
    createQuad(pos, size, color);
}

void Renderer::clear() const {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glClearColor(0.1f, 0.1, 0.1, 1.0f));
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

void Renderer::flush() {
    m_vao->setVertices(m_vertices);
    GL_CHECK(glDrawElements(GL_TRIANGLES, (m_vertices.size() / 4) * 6,
                            GL_UNSIGNED_INT, nullptr));
    m_vertices.clear();
}

void Renderer::begin() {
    m_framebuffer->bind();
    m_vao->bind();
    m_shader->bind();
    m_shader->setUniformMat4("u_mvp", m_camera->getTransform());
    clear();
}

void Renderer::end() {
    flush();
    m_framebuffer->unbind();
    m_vao->unbind();
}

GLuint Renderer::getData() const { return m_framebuffer->getTexture(); }

} // namespace Bess::Renderer2D
