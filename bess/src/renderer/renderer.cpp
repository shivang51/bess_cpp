#include "renderer/renderer.h"
#include "gl/framebuffer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer/camera.h"
#include "renderer/primitives/quad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

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
    glClearColor(0.1, 0.1, 0.1, 1.0f);
}

void Renderer::init() {
    m_camera = std::make_unique<Camera>();
    m_camera->resize(800, 500);
    m_framebuffer = std::make_unique<Gl::FrameBuffer>(800, 500);
}

void Renderer::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::resize(glm::vec2 size) const {
    m_camera->resize(size.x, size.y);
    m_framebuffer->resize(size.x, size.y);
    glViewport(0, 0, size.x, size.y);
}

Camera *Renderer::getCamera() { return m_camera.get(); }

ImVec2 Renderer::getFrameBufferSize() const { return m_framebuffer->getSize(); }

void Renderer::end() {
    ImGuiIO &io = ImGui::GetIO();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Renderer::beginScene() { m_framebuffer->bind(); }
void Renderer::endScene() { m_framebuffer->unbind(); }

GLuint Renderer::getData() const { return m_framebuffer->getTexture(); }

} // namespace Bess::Renderer2D
