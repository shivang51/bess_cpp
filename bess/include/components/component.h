#pragma once
#include "ext/vector_float2.hpp"

namespace Bess::Components {
class Component {
  public:
    Component(int id, glm::vec2 position);
    virtual ~Component() = default;

    virtual void render() = 0;

    int getId() const;
    glm::vec2 &getPosition();

  protected:
    int id;
    glm::vec2 position;
};
} // namespace Bess::Components
