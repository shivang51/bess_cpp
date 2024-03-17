#include "gl/utils.h"

namespace Bess::Gl::Utils {
Vertex createVertex(float x, float y) {
    Vertex v;
    v.position.x = x;
    v.position.y = y;
    v.position.z = 0.f;
    v.color.x = 1.f;
    v.color.y = 0.f;
    v.color.z = 0.f;
    return v;
}
} // namespace Bess::Gl::Utils
