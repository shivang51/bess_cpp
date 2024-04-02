#pragma once

#include "fwd.hpp"
#include "glad/glad.h"
#include "glm.hpp"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace Bess {

enum EntityType { none = -1, quad, curve };

struct Entity {
    glm::vec2 pos = {0.f, 0.f};
    glm::vec3 color = {1.f, 1.f, 1.f};
    int id = -1;

    EntityType type = EntityType::none;
};

struct UIState {
    float cameraZoom = 1.f;
    glm::vec2 cameraPos = {0.f, 0.f};
    glm::vec2 viewportSize = {800, 500};
    glm::vec2 viewportPos = {0, 0};
    GLuint64 viewportTexture = 0;

    std::unordered_map<int, Entity> entities = {};
    int hoveredId = -1;
    int selectedId = -1;
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
    static void ProjectExplorer();
    static void drawViewport();
    static void begin();
    static void end();
    static ImGuiID mainDockspaceId;
};
} // namespace Bess
