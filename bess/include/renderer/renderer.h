#pragma once

#include "gl/framebuffer.h"
#include "gl/shader.h"
#include "gl/vao.h"

#include "gl/vertex.h"
#include "renderer/camera.h"
#include <memory>

#include "camera.h"

namespace Bess::Renderer2D {
class Renderer {
  public:
    Renderer() = default;

    void init();

    void begin();

    void end();

    void quad(const glm::vec2 &pos, const glm::vec2 &size,
              const glm::vec3 &color);

    GLuint getData() const;

    Camera *getCamera();

    void clear() const;

    void resize(glm::vec2 size) const;

    glm::vec2 getFrameBufferSize() const;

  private:
    std::unique_ptr<Gl::Shader> m_shader;
    std::unique_ptr<Gl::Vao> m_vao;
    std::unique_ptr<Gl::FrameBuffer> m_framebuffer;
    std::unique_ptr<Renderer2D::Camera> m_camera;

    std::vector<Gl::Vertex> m_vertices = {};

    void flush();

    void createQuad(const glm::vec2 &pos, const glm::vec2 &size,
                    const glm::vec3 &color);
};

} // namespace Bess::Renderer2D
