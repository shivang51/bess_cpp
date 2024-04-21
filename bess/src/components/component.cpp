#include "components/component.h"

namespace Bess::Components {
Component::Component(int id, glm::vec2 position) : id(id), position(position) {}

int Component::getId() const { return id; }

glm::vec2 &Component::getPosition() { return position; }

} // namespace Bess::Components
