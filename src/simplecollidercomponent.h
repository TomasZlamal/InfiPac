#pragma once
#include "collider.h"

namespace pac {
struct RectangleRigidBody : public RigidBody2D {
  RectangleRigidBody(vec2 _wh, vec2 _pos) : RigidBody2D(_pos), wh(_wh) {}
  RectangleRigidBody(const RectangleRigidBody &rrb)
      : RigidBody2D(rrb.pos), wh(rrb.wh) {}
  vec2 wh; // width, height; ex. tl corner = pos - w/2 - h/2
};
class SimpleColliderComponent : public Collider {
  SimpleColliderComponent(RectangleRigidBody);
  bool isColliding(Collider *collider);
};

} // namespace pac
