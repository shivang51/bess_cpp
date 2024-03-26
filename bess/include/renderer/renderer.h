#pragma once

#include "gl/shader.h"
#include "gl/vao.h"

#include "gl/vertex.h"
#include "renderer/camera.h"
#include <memory>

#include "camera.h"

namespace Bess::Renderer2D {

struct RendererState {
    Camera *camera = nullptr;
};

class Renderer {
  public:
    Renderer() = default;

    static void init();

    static void begin();

    static void end();

    static void quad(const glm::vec2 &pos, const glm::vec2 &size,
                     const glm::vec3 &color, const int texture);

    static void curve(const glm::vec2 &start, const glm::vec2 &end,
                      const glm::vec3 &color, const int texture);

    static Camera *getCamera();

    static void resize(glm::vec2 size);

    static RendererState state;

  private:
    static std::unique_ptr<Gl::Shader> quad_shader;

    static std::unique_ptr<Gl::Vao> quad_vao;
    static std::unique_ptr<Gl::Vao> curve_vao;

    static std::unique_ptr<Renderer2D::Camera> m_camera;

    static std::vector<Gl::Vertex> quad_vertices;
    static std::vector<Gl::Vertex> curve_vertices;

    static void flushQuads();
    static void flushCurves();
};

} // namespace Bess::Renderer2D
