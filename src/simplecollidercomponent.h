#pragma once
#include "collider.h"
namespace pac {
struct vec2 {
  float x, y;
  vec2 operator/(const vec2 &a) { return {x / a.x, y / a.y}; }

  vec2 operator+(const vec2 &a) { return {x + a.x, y + a.y}; }
  vec2 operator-(const vec2 &a) { return {x - a.x, y - a.y}; }
};
struct RigidBody2D {};
struct RectangleRigidBody : public RigidBody2D {
  RectangleRigidBody(vec2 _wh, vec2 _pos) : pos(_pos), wh(_wh) {}
  RectangleRigidBody(const RectangleRigidBody &rrb)
      : pos(rrb.pos), wh(rrb.wh) {}
  vec2 pos; // center of obj
  vec2 wh;  // width, height; ex. tl corner = pos - w/2 - h/2
};
class SimpleColliderComponent : public Collider {
  RectangleRigidBody m_rigidbody;

public:
  SimpleColliderComponent(RectangleRigidBody);
  bool isColliding(Collider *collider);
};

} // namespace pac
