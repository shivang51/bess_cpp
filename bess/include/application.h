#pragma once

#include "renderer/renderer.h"
#include "window.h"

namespace Bess {
class Application {
  public:
    Application();
    ~Application();

    void run();
    void quit();

  private:
    Window m_window;
    Renderer2D::Renderer m_renderer;

  private:
    void drawUI();
    void drawScene();
};
} // namespace Bess
