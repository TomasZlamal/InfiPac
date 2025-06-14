#include "simplecollidercomponent.h"
#include "debug.h"
#include <cstdlib>
#include <memory>

namespace pac {
vec2 SimpleColliderComponent::isColliding(Collider *collider) {
  if (auto dyn = dynamic_cast<SimpleColliderComponent *>(collider)) {
    // TODO: Change this to cast the rrb to a rect
    std::shared_ptr<pac::RectangleRigidBody> rrb =
        std::dynamic_pointer_cast<pac::RectangleRigidBody>(this->m_rigidbody);
    // check if any of the points are inside of the other rectangle
    vec2 points_a[] = {rrb->pos - vec2{rrb->wh.x / 2, rrb->wh.y / 2},  // tl
                       rrb->pos - vec2{rrb->wh.x / 2, -rrb->wh.y / 2}, // bl
                       rrb->pos + vec2{rrb->wh.x / 2, -rrb->wh.y / 2}, // tr
                       rrb->pos + vec2{rrb->wh.x / 2, rrb->wh.y / 2},  // br
                       rrb->pos};
    const pac::RectangleRigidBody *rrb2 =
        dynamic_cast<const pac::RectangleRigidBody *>(
            dyn->getRigidBody().get());
    if (rrb2 == rrb.get()) {
      DEBUG_PRINT("INFO: Comparing equivalent rigid bodies.")
      return {};
    }

    int a = 0;
    uint8_t b = 0;
    vec2 total{};
    float dir = 0;
    for (vec2 point : points_a) {
      if (RectangleRigidBody::rrb_point_collision(rrb2, point) == 1) {

        float x, y;
        // missing "4" arm
        switch (a) {
        case 0:
          x = rrb2->pos.x + rrb2->wh.x / 2;
          y = rrb2->pos.y + rrb2->wh.y / 2;
          b += 1;
          break;
        case 1:
          x = rrb2->pos.x + rrb2->wh.x / 2;
          y = rrb2->pos.y - rrb2->wh.y / 2;
          b += 2;
          break;
        case 2:
          x = rrb2->pos.x - rrb2->wh.x / 2;
          y = rrb2->pos.y + rrb2->wh.y / 2;
          b += 4;
          break;
        case 3:
          x = rrb2->pos.x - rrb2->wh.x / 2;
          y = rrb2->pos.y - rrb2->wh.y / 2;
          b += 8;
          break;
        default:
          break;
        }
        DEBUG_PRINT(a)
        total = points_a[a] - vec2{x, y};
        // dir =
      }
      a++;
    }

    if (!(0b00001010 ^ b) || !(0b00000101 ^ b)) {
      return vec2{0, total.y};
    }
    if (!(0b00000011 ^ b) || !(0b00001100 ^ b)) {
      return vec2{total.x, 0};
    }
    if (std::abs(total.x) < std::abs(total.y)) {
      return vec2{total.x, 0};
    }
    return vec2{0, total.y};
  }
  return {};
}

vec2 RectangleRigidBody::getCenter() {
  return vec2{pos.x - wh.x, pos.y - wh.y};
}
} // namespace pac
