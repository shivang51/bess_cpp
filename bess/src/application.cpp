#include "application.h"
#include "fwd.hpp"
#include "ui.h"

namespace Bess {
Application::Application() : m_window(800, 600, "Bess") {
    m_window.onWindowResize([](int w, int h) {
        // glViewport(0, 0, w, h);
    });

    m_window.onMouseWheel([](double x, double y) {
        float delta = y * 0.1f;
        UI::state.cameraZoom += delta;
        if (UI::state.cameraZoom < 0.1f) {
            UI::state.cameraZoom = 0.1f;
        } else if (UI::state.cameraZoom > 2.0f) {
            UI::state.cameraZoom = 2.f;
        }
    });
    m_renderer.init();
}

Application::~Application() { m_window.close(); }

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

} // namespace Bess
