#pragma once
#include "component.h"
#include "ext/vector_float2.hpp"

namespace Bess::Components {
class NandGate : public Component {
  public:
    NandGate(int id, glm::vec2 position);
    ~NandGate() = default;

    void render() override;
};
} // namespace Bess::Components
