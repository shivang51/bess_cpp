#include "components/nand_gate.h"

#include "fwd.hpp"
#include "renderer/renderer.h"
#include "ui.h"

namespace Bess::Components {

glm::vec3 borderColor = {0.42f, 0.42f, 0.42f};
glm::vec3 selectedBorderColor = {0.8f, 0.3f, 0.3f};

NandGate::NandGate(int id, glm::vec2 position) : Component(id, position) {}

void NandGate::render() {
    bool selected = UI::state.selectedId == id;
    float thickness = selected ? 0.005 : 0.003;
    Renderer2D::Renderer::quad(
        {position.x - thickness, position.y + thickness},
        {0.3f + (thickness * 2), 0.25f + (thickness * 2)},
        selected ? selectedBorderColor : borderColor, id);

    Renderer2D::Renderer::quad(position, {0.3f, 0.25f}, {.22f, .22f, 0.22f},
                               id);
    Renderer2D::Renderer::quad(position, {0.3f, 0.05f}, {.490f, .525, 0.858f},
                               id);

    Renderer2D::Renderer::circle(position + glm::vec2({0.025, -0.09f}), 0.015,
                                 borderColor, Renderer2D::Renderer::getSubId());

    Renderer2D::Renderer::circle(position + glm::vec2({0.025, -0.22f}), 0.015,
                                 borderColor, Renderer2D::Renderer::getSubId());

    Renderer2D::Renderer::circle(position + glm::vec2({0.3 - 0.025, -0.155f}),
                                 0.015, borderColor,
                                 Renderer2D::Renderer::getSubId());
}

} // namespace Bess::Components
