#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Bess {
struct UIState {
    float cameraZoom = 1.f;
    glm::vec2 cameraPos = {0.f, 0.f};
    glm::vec2 viewportSize = {800, 500};
    GLuint64 viewportTexture = 0;
};

class UI {
  public:
    static void draw();

    static void setViewportTexture(GLuint64 texture);

    static UIState state;

  private:
    static void drawSettings();
    static void drawViewport();
    static void begin();
    static void end();
};
} // namespace Bess
