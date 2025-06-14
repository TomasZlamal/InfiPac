#pragma once
#include "debug.h"
namespace pac {
struct vec2 {
  float x, y;
  vec2 operator/(const vec2 &a) { return {x / a.x, y / a.y}; }

  vec2 operator+(const vec2 &a) { return vec2{x + a.x, y + a.y}; }
  vec2 operator-(const vec2 &a) { return vec2{x - a.x, y - a.y}; }
  vec2 operator-() { return vec2{-x, -y}; }
  vec2 operator*(float a) { return vec2{x * a, y * a}; }
  vec2 operator/(float a) { return vec2{x / a, y / a}; }
  vec2 operator-(float a) { return vec2{x - a, y - a}; }
  operator bool() { return x != 0 || y != 0; }
#ifdef DEBUG_MODE_ON
  void getPrint() {
    std::cout << "Vec2:" << "\n{ " << x << ",\n " << y << "\n}" << std::endl;
  }
#endif
};

struct RigidBody2D {
  virtual ~RigidBody2D() = default;
  RigidBody2D(vec2 _pos) : pos(_pos), weight(1.0f) {}
  RigidBody2D(vec2 _pos, float _weight) : pos(_pos), weight(_weight) {}
  virtual vec2 getCenter() = 0;
  float weight;

  vec2 pos; // center of obj
};
} // namespace pac
