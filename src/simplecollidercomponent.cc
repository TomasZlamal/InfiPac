#include "simplecollidercomponent.h"
#include "debug.h"
#include <memory>

namespace pac {
vec2 SimpleColliderComponent::isColliding(Collider *collider) {
  if (auto dyn = dynamic_cast<SimpleColliderComponent *>(collider)) {
    // TODO: Change this to cast the rrb to a rect
    std::shared_ptr<pac::RectangleRigidBody> rrb =
        std::dynamic_pointer_cast<pac::RectangleRigidBody>(m_rigidbody);
    // check if any of the points are inside of the other rectangle
    vec2 points_a[] = {rrb->pos - vec2{rrb->wh.x / 2, rrb->wh.y / 2},
                       rrb->pos - vec2{rrb->wh.x / 2, -rrb->wh.y / 2},
                       rrb->pos + vec2{rrb->wh.x / 2, -rrb->wh.y / 2},
                       rrb->pos + vec2{rrb->wh.x / 2, rrb->wh.y / 2}, rrb->pos};
    const pac::RectangleRigidBody *rrb2 =
        dynamic_cast<const pac::RectangleRigidBody *>(
            dyn->getRigidBody().get());
    for (vec2 point : points_a) {
      // generic point rect collision logic; should move to indep. function
      // TODO: REDO THIS WHOLE LOGIC
      if (point.x <= (rrb2->pos.x + rrb2->wh.x / 2) &&
          point.x >= (rrb2->pos.x - rrb2->wh.x / 2) &&
          point.y <= (rrb2->pos.y + rrb2->wh.y / 2) &&
          point.y >= (rrb2->pos.y - rrb2->wh.y / 2)) {
        return {};
      }
    }

    return {};
  }
  return {};
}
} // namespace pac
