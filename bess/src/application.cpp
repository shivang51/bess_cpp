#include "application.h"
#include "components/nand_gate.h"
#include "fwd.hpp"
#include "gl/framebuffer.h"
#include "renderer/renderer.h"
#include "ui.h"
#include <GLFW/glfw3.h>
#include <unordered_map>

using Bess::Renderer2D::Renderer;

namespace Bess {

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this)

#define BIND_EVENT_FN_1(fn)                                                    \
    std::bind(&Application::fn, this, std::placeholders::_1)

#define BIND_EVENT_FN_2(fn)                                                    \
    std::bind(&Application::fn, this, std::placeholders::_1,                   \
              std::placeholders::_2)

Application::Application() : m_window(800, 600, "Bess") {

    m_framebuffer = std::make_unique<Gl::FrameBuffer>(800, 500);
    m_camera = std::make_shared<Camera>();

    UI::init(m_window.getGLFWHandle());
    UI::state.viewportTexture = m_framebuffer->getTexture();

    Renderer::init();

    m_window.onWindowResize(BIND_EVENT_FN_2(onWindowResize));
    m_window.onMouseWheel(BIND_EVENT_FN_2(onMouseWheel));
    m_window.onKeyPress(BIND_EVENT_FN_1(onKeyPress));
    m_window.onKeyRelease(BIND_EVENT_FN_1(onKeyRelease));
    m_window.onLeftMouse(BIND_EVENT_FN_1(onLeftMouse));
    m_window.onRightMouse(BIND_EVENT_FN_1(onRightMouse));
    m_window.onMiddleMouse(BIND_EVENT_FN_1(onMiddleMouse));
    m_window.onMouseMove(BIND_EVENT_FN_2(onMouseMove));

    auto &comps = UI::state.components;
    int n = 2;
    while (n--) {
        int id = Renderer::getId();
        comps[id] =
            std::make_unique<Components::NandGate>(id, glm::vec2(0.f, 0.f));
    }
}

Application::~Application() {
    UI::shutdown();
    m_window.close();
}

void Application::drawUI() {
    UI::draw();

    if (m_framebuffer->getSize() != UI::state.viewportSize) {
        m_framebuffer->resize(UI::state.viewportSize.x,
                              UI::state.viewportSize.y);
        m_camera->resize(UI::state.viewportSize.x, UI::state.viewportSize.y);
    }

    if (UI::state.cameraZoom != m_camera->getZoom()) {
        m_camera->setZoom(UI::state.cameraZoom);
    }

    if (UI::state.cameraPos != m_camera->getPos()) {
        m_camera->setPos(UI::state.cameraPos);
    }
}

void Application::drawScene() {
    m_framebuffer->bind();

    Renderer::begin(m_camera);

    bool rendered = true;

    for (auto &[id, entity] : UI::state.components) {
        entity->render();
    }

    Renderer::end();

    if (isCursorInViewport()) {
        auto viewportMousePos = getViewportMousePos();
        viewportMousePos.y = UI::state.viewportSize.y - viewportMousePos.y;
        UI::state.hoveredId =
            m_framebuffer->readId(viewportMousePos.x, viewportMousePos.y);
    }

    m_framebuffer->unbind();
}

void Application::run() {
    while (!m_window.isClosed()) {
        m_window.waitEventsTimeout(0.0167);

        drawScene();
        drawUI();

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
        } else if (UI::state.cameraZoom > 6.0f) {
            UI::state.cameraZoom = 6.f;
        }
    } else {
        UI::state.cameraPos.y -= delta;
    }
}

void Application::onKeyPress(int key) { m_pressedKeys[key] = true; }

void Application::onKeyRelease(int key) { m_pressedKeys[key] = false; }

void Application::onLeftMouse(bool pressed) {
    m_leftMousePressed = pressed;

    if (!pressed || !isCursorInViewport())
        return;

    UI::state.selectedId = UI::state.hoveredId;
}

void Application::onRightMouse(bool pressed) { m_rightMousePressed = pressed; }

void Application::onMiddleMouse(bool pressed) {
    m_middleMousePressed = pressed;
}

void Application::onMouseMove(double x, double y) {
    double dx = x - m_mousePos.x;
    double dy = y - m_mousePos.y;
    m_mousePos = {x, y};

    if (!isCursorInViewport())
        return;

    if (m_middleMousePressed) {
        UI::state.cameraPos.x -= (dx * 0.002) / UI::state.cameraZoom;
        UI::state.cameraPos.y -= (dy * 0.002) / UI::state.cameraZoom;
    } else if (m_leftMousePressed && UI::state.selectedId > 0 &&
               UI::state.components.find(UI::state.selectedId) !=
                   UI::state.components.end()) {
        auto &entity = UI::state.components[UI::state.selectedId];
        auto &pos = entity->getPosition();
        pos.x += (dx * 0.002) / UI::state.cameraZoom;
        pos.y -= (dy * 0.002) / UI::state.cameraZoom;
    }
}

bool Application::isCursorInViewport() {
    const auto &viewportPos = UI::state.viewportPos;
    const auto &viewportSize = UI::state.viewportSize;
    return m_mousePos.x > viewportPos.x &&
           m_mousePos.x < viewportPos.x + viewportSize.x &&
           m_mousePos.y > viewportPos.y &&
           m_mousePos.y < viewportPos.y + viewportSize.y;
}

glm::vec2 Application::getViewportMousePos() {
    const auto &viewportPos = UI::state.viewportPos;
    const auto &viewportSize = UI::state.viewportSize;
    auto x = m_mousePos.x - viewportPos.x;
    auto y = m_mousePos.y - viewportPos.y;
    return {x, y};
}

} // namespace Bess
