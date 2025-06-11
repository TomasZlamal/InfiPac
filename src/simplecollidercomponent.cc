#include "simplecollidercomponent.h"
#include "debug.h"

namespace pac {
bool SimpleColliderComponent::isColliding(Collider *collider) {
  if (auto dyn = dynamic_cast<SimpleColliderComponent *>(collider)) {

    // check if any of the points are inside of the other rectangle
    vec2 points_a[] = {
        m_rigidbody.pos - vec2{m_rigidbody.wh.x / 2, m_rigidbody.wh.y / 2},
        m_rigidbody.pos - vec2{m_rigidbody.wh.x / 2, -m_rigidbody.wh.y / 2},
        m_rigidbody.pos + vec2{m_rigidbody.wh.x / 2, -m_rigidbody.wh.y / 2},
        m_rigidbody.pos + vec2{m_rigidbody.wh.x / 2, m_rigidbody.wh.y / 2},
        m_rigidbody.pos};
    for (vec2 point : points_a) {
      // generic point rect collision logic; should move to indep. function
      if (point.x <= (dyn->m_rigidbody.pos.x + dyn->m_rigidbody.wh.x / 2) &&
          point.x >= (dyn->m_rigidbody.pos.x - dyn->m_rigidbody.wh.x / 2) &&
          point.y <= (dyn->m_rigidbody.pos.y + dyn->m_rigidbody.wh.y / 2) &&
          point.y >= (dyn->m_rigidbody.pos.y - dyn->m_rigidbody.wh.y / 2)) {
        return true;
      }
    }

    return false;
  }
  return false;
}
SimpleColliderComponent::SimpleColliderComponent(RectangleRigidBody rrb)
    : m_rigidbody(rrb) {}
} // namespace pac
