#pragma once

#include "gl/framebuffer.h"
#include "gl/ibo.h"
#include "gl/shader.h"
#include "gl/vao.h"

#include "imgui.h"
#include "primitives/quad.h"
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

    void beginScene();
    void endScene();

    void draw(const Gl::Vao &vao, const Gl::Ibo &ibo,
              const Gl::Shader &shader) const;

    void quad();

    GLuint getData() const;

    Camera *getCamera();

    void clear() const;

    void resize(glm::vec2 size) const;

    ImVec2 getFrameBufferSize() const;

  private:
    std::unique_ptr<Primitives::Quad> m_quad;
    std::unique_ptr<Gl::FrameBuffer> m_framebuffer;
    std::unique_ptr<Renderer2D::Camera> m_camera;
};

} // namespace Bess::Renderer2D
