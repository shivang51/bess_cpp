#pragma once

#include "fwd.hpp"
#include "glad/glad.h"
#include "glm.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>

namespace Bess {
struct UIState {
    float cameraZoom = 1.f;
    glm::vec2 cameraPos = {0.f, 0.f};
    glm::vec2 viewportSize = {800, 500};
    glm::vec2 viewportPos = {0, 0};
    GLuint64 viewportTexture = 0;
};

class UI {
  public:
    static void init(GLFWwindow *window);

    static void shutdown();

    static void draw();

    static void setViewportTexture(GLuint64 texture);

    static UIState state;

    static glm::vec2 dPos;
    static glm::vec2 dSize;

  private:
    static void setDarkThemeColors();
    static void drawSettings();
    static void drawViewport();
    static void begin();
    static void end();
    static ImGuiID mainDockspaceId;
};
} // namespace Bess
