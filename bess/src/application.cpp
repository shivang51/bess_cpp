#include "application.h"
#include "fwd.hpp"
#include "ui.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Bess {

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this)

#define BIND_EVENT_FN_1(fn)                                                    \
    std::bind(&Application::fn, this, std::placeholders::_1)

#define BIND_EVENT_FN_2(fn)                                                    \
    std::bind(&Application::fn, this, std::placeholders::_1,                   \
              std::placeholders::_2)

Application::Application() : m_window(800, 600, "Bess") {

    UI::init(m_window.getGLFWHandle());
    m_renderer.init();

    m_window.onWindowResize(BIND_EVENT_FN_2(onWindowResize));
    m_window.onMouseWheel(BIND_EVENT_FN_2(onMouseWheel));
    m_window.onKeyPress(BIND_EVENT_FN_1(onKeyPress));
    m_window.onKeyRelease(BIND_EVENT_FN_1(onKeyRelease));
    m_window.onLeftMouse(BIND_EVENT_FN_1(onLeftMouse));
    m_window.onRightMouse(BIND_EVENT_FN_1(onRightMouse));
    m_window.onMiddleMouse(BIND_EVENT_FN_1(onMiddleMouse));
    m_window.onMouseMove(BIND_EVENT_FN_2(onMouseMove));
}

Application::~Application() {
    UI::shutdown();
    m_window.close();
}

void Application::drawUI() {
    if (UI::state.viewportTexture != m_renderer.getData()) {
        UI::state.viewportTexture = m_renderer.getData();
    }

    UI::draw();

    if (m_renderer.getFrameBufferSize() != UI::state.viewportSize) {
        m_renderer.resize(UI::state.viewportSize);
    }

    auto camera = m_renderer.getCamera();

    if (UI::state.cameraZoom != camera->getZoom()) {
        camera->setZoom(UI::state.cameraZoom);
    }

    if (UI::state.cameraPos != camera->getPos()) {
        camera->setPos(UI::state.cameraPos);
    }
}

void Application::drawScene() {
    m_renderer.begin();

    for (float y = -10.0; y <= 10.0; y += 0.25) {
        for (float x = -10.0; x <= 10.0; x += 0.25) {
            glm::vec3 color = {(x + 10.0) / 20.0, 0.2f, (y + 10.0) / 4.0};
            m_renderer.quad({x, y}, {0.25, 0.25}, color);
        }
    }

    m_renderer.quad(UI::dPos, UI::dSize, {0.9f, 0.6f, 0.4f});
    m_renderer.quad({UI::dPos.x / 2, UI::dPos.y / 2},
                    {UI::dSize.x / 2, UI::dSize.y / 2}, {1.f, 1.f, 1.f});

    m_renderer.end();
}

void Application::run() {
    while (!m_window.isClosed()) {
        m_window.pollEvents();

        drawUI();
        drawScene();

        m_window.update();
    }
}

void Application::quit() { m_window.close(); }

bool Application::isKeyPressed(int key) { return m_pressedKeys[key]; }

// callbacks

void Application::onWindowResize(int w, int h) {
    // glViewport(0, 0, w, h);
}

void Application::onMouseWheel(double x, double y) {
    float delta = y * 0.1f;

    if (isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        UI::state.cameraZoom += delta;
        if (UI::state.cameraZoom < 0.1f) {
            UI::state.cameraZoom = 0.1f;
        } else if (UI::state.cameraZoom > 2.0f) {
            UI::state.cameraZoom = 2.f;
        }
    } else {
        UI::state.cameraPos.y -= delta;
    }
}

void Application::onKeyPress(int key) { m_pressedKeys[key] = true; }

void Application::onKeyRelease(int key) { m_pressedKeys[key] = false; }

void Application::onLeftMouse(bool pressed) {
    m_leftMousePressed = pressed;
    if (!pressed)
        return;

    std::cout << "Clicked at" << m_preMousePos.x << " " << m_preMousePos.y
              << std::endl;

    const auto &viewportPos = UI::state.viewportPos;
    const auto &viewportSize = UI::state.viewportSize;

    if (m_preMousePos.x > viewportPos.x &&
        m_preMousePos.x < viewportPos.x + viewportSize.x &&
        m_preMousePos.y > viewportPos.y &&
        m_preMousePos.y < viewportPos.y + viewportSize.y) {
        std::cout << "Clicked inside viewport" << std::endl;
    }
}

void Application::onRightMouse(bool pressed) { m_rightMousePressed = pressed; }

void Application::onMiddleMouse(bool pressed) {
    m_middleMousePressed = pressed;
}

void Application::onMouseMove(double x, double y) {
    double dx = x - m_preMousePos.x;
    double dy = y - m_preMousePos.y;

    if (m_middleMousePressed) {
        UI::state.cameraPos.x -= (dx * 0.002) / UI::state.cameraZoom;
        UI::state.cameraPos.y -= (dy * 0.002) / UI::state.cameraZoom;
    }

    m_preMousePos = {x, y};
}

} // namespace Bess
