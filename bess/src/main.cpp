#include "gl/shader.h"
#include "gl/vao.h"
#include "renderer/renderer.h"
#include "window.h"
#include <vector>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

extern "C" {
#include "glad/glad.h"
}

#include <GLFW/glfw3.h>

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

Bess::Gl::Vertex createVertex(float x, float y) {
    Bess::Gl::Vertex v;
    v.position.x = x;
    v.position.y = y;
    v.position.z = 0.f;
    v.color.x = 1.f;
    v.color.y = 0.f;
    v.color.z = 0.f;
    return v;
}

int main() {

    auto window = Bess::Window(800, 600, "BESS");

    std::vector<Bess::Gl::Vertex> vertices = {
        createVertex(0.0f, 0.0f),
        createVertex(0.5f, 0.f),
        createVertex(0.f, 0.5f),
        createVertex(0.5f, 0.5f),
    };

    std::vector<GLuint> indices = {0, 1, 2, 2, 3, 1};

    Bess::Gl::Vao vao(vertices);
    Bess::Gl::Ibo ibo(indices);
    auto shaderProgram = Bess::Gl::Shader("bess/src/shaders/first_vert.glsl",
                                          "bess/src/shaders/first_frag.glsl");

    window.onWindowResize([](int w, int h) { glViewport(0, 0, w, h); });

    Bess::Gl::Renderer renderer;
    while (!window.isClosed()) {
        window.pollEvents();
        renderer.clear();
        renderer.draw(vao, ibo, shaderProgram);
        renderer.begin();
        ImGui::ShowDemoWindow();
        renderer.end();

        window.update();
    }

    return 0;
}
