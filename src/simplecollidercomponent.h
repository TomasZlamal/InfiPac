#pragma once
#include "collider.h"
#include "rigidbody.h"

namespace pac {
struct RectangleRigidBody : public RigidBody2D,
                            std::enable_shared_from_this<RectangleRigidBody> {
  RectangleRigidBody() : RigidBody2D({0, 0}), wh(vec2{0, 0}) {}
  RectangleRigidBody(vec2 _wh, vec2 _pos) : RigidBody2D(_pos), wh(_wh) {}
  RectangleRigidBody(const RectangleRigidBody &rrb)
      : RigidBody2D(rrb.pos), wh(rrb.wh) {}
  vec2 wh; // width, height; ex. tl corner = pos - w/2 - h/2
};
class SimpleColliderComponent : public Collider {
public:
  using Collider::Collider;
  vec2 isColliding(Collider *collider);
};

} // namespace pac
