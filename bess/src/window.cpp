extern "C" {
#include "glad/glad.h"
}
#include "window.h"
#include <iostream>
#include <memory>

namespace Bess {
bool Window::isGLFWInitialized = false;
bool Window::isGladInitialized = false;

Window::Window(int width, int height, const std::string &title) {
    if (!isGLFWInitialized) {
        glfwInit();
        isGLFWInitialized = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window =
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetWindowUserPointer(window, this);

    mp_window = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(window);

    this->makeCurrent();

    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *window, int w, int h) {
            auto this_ = (Window *)glfwGetWindowUserPointer(window);
            if (this_->m_callbacks.find(Callback::WindowResize) ==
                this_->m_callbacks.end())
                return;
            auto cb = std::any_cast<WindowResizeCallback>(
                this_->m_callbacks[Callback::WindowResize]);
            cb(w, h);
        });

    if (!isGladInitialized) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        } else {
            isGladInitialized = true;
        }
    }
}

Window::~Window() {
    this->mp_window.reset();
    glfwTerminate();
}

void Window::update() const { glfwSwapBuffers(mp_window.get()); }

void Window::makeCurrent() const { glfwMakeContextCurrent(mp_window.get()); }

bool Window::isClosed() const { return glfwWindowShouldClose(mp_window.get()); }

void Window::onWindowResize(WindowResizeCallback callback) {
    m_callbacks[Callback::WindowResize] = callback;
}

} // namespace Bess
