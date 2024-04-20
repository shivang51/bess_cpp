#pragma once

#include "gl/shader.h"
#include "gl/vao.h"

#include "gl/vertex.h"
#include "renderer/camera.h"
#include <memory>
#include <unordered_map>

#include "camera.h"

namespace Bess::Renderer2D {
enum class PrimitiveType { quad, curve, circle };

class Renderer {
  public:
    Renderer() = default;

    static void init();

    static void begin(std::shared_ptr<Renderer2D::Camera> camera);
    static void end();

    static void quad(const glm::vec2 &pos, const glm::vec2 &size,
                     const glm::vec3 &color, const int id);

    static void quad(const glm::vec2 &pos, const glm::vec2 &size,
                     const glm::vec3 &color, const int id, const float angle);

    static void curve(const glm::vec2 &start, const glm::vec2 &end,
                      const glm::vec3 &color, const int id);

    static void circle(const glm::vec2 &center, const float radius,
                       const glm::vec3 &color, const int id);

  private:
    static glm::vec2 createCurveVertices(const glm::vec2 &start,
                                         const glm::vec2 &end,
                                         const glm::vec3 &color, const int id);

  private:
    static void addVertices(PrimitiveType type,
                            const std::vector<Gl::Vertex> &vertices);

  private:
    static std::unordered_map<PrimitiveType, std::unique_ptr<Gl::Shader>>
        m_shaders;
    static std::unordered_map<PrimitiveType, std::unique_ptr<Gl::Vao>> m_vaos;
    static std::unordered_map<PrimitiveType, std::vector<Gl::Vertex>>
        m_vertices;

    static std::unordered_map<PrimitiveType, size_t> m_maxRenderCount;

    static std::shared_ptr<Renderer2D::Camera> m_camera;

    static std::vector<PrimitiveType> m_AvailablePrimitives;

    static void flush(PrimitiveType type);

    static std::vector<glm::vec4> m_QuadVertices;
};

} // namespace Bess::Renderer2D
