#include "application.h"
#include "gl/utils.h"
#include "renderer/primitives/quad.h"
#include "renderer/renderer.h"
#include "ui.h"
#include <iostream>

namespace Bess {
Application::Application() : m_window(800, 600, "Bess") {
    m_window.onWindowResize([](int w, int h) {
        // glViewport(0, 0, w, h);
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
    m_renderer.beginScene();
    m_renderer.clear();
    m_renderer.quad();
    m_renderer.endScene();
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
