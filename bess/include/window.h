#pragma once

#include <GLFW/glfw3.h>
#include <algorithm>
#include <any>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace Bess {

enum Callback {
    WindowResize,
};

typedef std::function<void(int, int)> WindowResizeCallback;

class Window {
  public:
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window) { glfwDestroyWindow(window); }
    };

    Window(int width, int height, const std::string &title);
    ~Window();

    void update() const;
    void makeCurrent() const;
    bool isClosed() const;

    inline void pollEvents() const { glfwPollEvents(); }

    static bool isGLFWInitialized;
    static bool isGladInitialized;

    void onWindowResize(WindowResizeCallback callback);

  private:
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> mp_window;
    std::unordered_map<Callback, std::any> m_callbacks;
};
} // namespace Bess
