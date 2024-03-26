#include "renderer/renderer.h"
#include "fwd.hpp"
#include "gl/gl_wrapper.h"
#include "gl/vertex.h"
#include "renderer/camera.h"
#include "ui.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace Bess::Renderer2D {

const size_t MAX_QUADS = 250;
const size_t MAX_CURVES = 250;

RendererState Renderer::state;

std::unique_ptr<Gl::Shader> Renderer::quad_shader;

std::unique_ptr<Gl::Vao> Renderer::quad_vao;

std::unique_ptr<Gl::Vao> Renderer::curve_vao;

std::unique_ptr<Camera> Renderer::m_camera;

std::vector<Gl::Vertex> Renderer::quad_vertices;

std::vector<Gl::Vertex> Renderer::curve_vertices;

void Renderer::init() {
    state = {};
    quad_vertices = {};
    curve_vertices = {};

    quad_shader = std::make_unique<Gl::Shader>(
        "bess/src/shaders/first_vert.glsl", "bess/src/shaders/first_frag.glsl");

    quad_vao = std::make_unique<Gl::Vao>(MAX_QUADS * 4, MAX_QUADS * 6);
    curve_vao = std::make_unique<Gl::Vao>(MAX_CURVES * 4, MAX_CURVES * 6);

    m_camera = std::make_unique<Camera>();
}

void Renderer::quad(const glm::vec2 &pos, const glm::vec2 &size,
                    const glm::vec3 &color, const int texture) {
    if (quad_vertices.size() >= (MAX_QUADS - 1) * 4) {
        flushQuads();
    }

    std::vector<Gl::Vertex> vertices(4);

    vertices[0].position = {pos.x, pos.y, 0.0f};
    vertices[1].position = {pos.x, pos.y - size.y, 0.0f};
    vertices[2].position = {pos.x + size.x, pos.y - size.y, 0.0f};
    vertices[3].position = {pos.x + size.x, pos.y, 0.0f};

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    vertices[1].texCoord = {0.0f, 0.0f};
    vertices[0].texCoord = {0.0f, 1.0f};
    vertices[3].texCoord = {1.0f, 1.0f};
    vertices[2].texCoord = {1.0f, 0.0f};

    vertices[0].texIndex = texture;
    vertices[1].texIndex = texture;
    vertices[2].texIndex = texture;
    vertices[3].texIndex = texture;

    quad_vertices.insert(quad_vertices.end(), vertices.begin(), vertices.end());
}

void Renderer::curve(const glm::vec2 &start, const glm::vec2 &end,
                     const glm::vec3 &color, const int texture) {
    if (curve_vertices.size() >= (MAX_CURVES - 1) * 4) {
        flushCurves();
    }

    std::vector<Gl::Vertex> vertices(4);

    vertices[0].position = {start.x, start.y, 0.0f};
    vertices[1].position = {start.x, end.y, 0.0f};
    vertices[2].position = {end.x, end.y, 0.0f};
    vertices[3].position = {end.x, start.y, 0.0f};

    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;

    vertices[1].texCoord = {0.0f, 0.0f};
    vertices[0].texCoord = {0.0f, 1.0f};
    vertices[3].texCoord = {1.0f, 1.0f};
    vertices[2].texCoord = {1.0f, 0.0f};

    vertices[0].texIndex = texture;
    vertices[1].texIndex = texture;
    vertices[2].texIndex = texture;
    vertices[3].texIndex = texture;

    curve_vertices.insert(curve_vertices.end(), vertices.begin(),
                          vertices.end());
}

void Renderer::resize(glm::vec2 size) { m_camera->resize(size.x, size.y); }

Camera *Renderer::getCamera() { return m_camera.get(); }

void Renderer::flushQuads() {
    quad_vao->bind();
    quad_shader->bind();
    quad_shader->setUniformMat4("u_mvp", m_camera->getTransform());

    auto selId = UI::state.selectedId;

    if (selId != -1) {
        quad_shader->setUniform1i("u_SelectedObjId", selId);
    }

    quad_vao->setVertices(quad_vertices);
    GL_CHECK(glDrawElements(GL_TRIANGLES, (quad_vertices.size() / 4) * 6,
                            GL_UNSIGNED_INT, nullptr));
    quad_vertices.clear();
    quad_vao->unbind();
    quad_shader->unbind();
}

void Renderer::flushCurves() {
    curve_vao->bind();

    auto selId = UI::state.selectedId;

    quad_shader->bind();
    quad_shader->setUniformMat4("u_mvp", m_camera->getTransform());

    if (selId != -1) {
        quad_shader->setUniform1i("u_SelectedObjId", selId);
    }

    curve_vao->setVertices(curve_vertices);

    GL_CHECK(glDrawElements(GL_TRIANGLES, (curve_vertices.size() / 4) * 6,
                            GL_UNSIGNED_INT, nullptr));
    curve_vertices.clear();

    curve_vao->unbind();
    quad_shader->unbind();
}

void Renderer::begin() {}

void Renderer::end() { flushQuads(); }

} // namespace Bess::Renderer2D
