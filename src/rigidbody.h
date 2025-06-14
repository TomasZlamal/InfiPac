#pragma once
#include "math_structs.h"
namespace pac {
struct RigidBody2D {
  virtual ~RigidBody2D() = default;
  RigidBody2D(vec2 _pos) : pos(_pos), weight(1.0f) {}
  RigidBody2D(vec2 _pos, float _weight) : pos(_pos), weight(_weight) {}
  virtual vec2 getCenter() = 0;
  float weight;

  vec2 pos; // center of obj
};
} // namespace pac
