#pragma once
#include "collider.h"
#include "debug.h"
#include "rigidbody.h"

namespace pac {
struct RectangleRigidBody : public RigidBody2D,
                            std::enable_shared_from_this<RectangleRigidBody> {
  RectangleRigidBody() : RigidBody2D({0, 0}), wh(vec2{0, 0}) {}
  RectangleRigidBody(vec2 _wh, vec2 _pos) : RigidBody2D(_pos), wh(_wh) {}
  RectangleRigidBody(vec2 _wh, vec2 _pos, float _weight)
      : RigidBody2D(_pos, _weight), wh(_wh) {}
  RectangleRigidBody(const RectangleRigidBody &rrb)
      : RigidBody2D(rrb.pos), wh(rrb.wh) {}

  vec2 getCenter();
  vec2 wh; // width, height; ex. tl corner = pos - w/2 - h/2
  static bool rrb_point_collision(const RectangleRigidBody *rrb, vec2 point) {
    vec2 points_a[] = {
        vec2{rrb->pos} - vec2{rrb->wh.x / 2, rrb->wh.y / 2}, // tl
        vec2{rrb->pos} + vec2{rrb->wh.x / 2, rrb->wh.y / 2}  // br
    };
    vec2 d1 = point - points_a[0];
    vec2 d2 = point - points_a[1];
    /*#ifdef DEBUG_MODE_ON
        points_a[0].getPrint();
        points_a[1].getPrint();
        point.getPrint();
    #endif*/
    if (d1.x > 0 && d1.y > 0 && d2.x < 0 && d2.y < 0) {
      return 1;
    }
    return 0;
  }
};
class SimpleColliderComponent : public Collider {
public:
  using Collider::Collider;
  vec2 isColliding(Collider *collider);
};

} // namespace pac
