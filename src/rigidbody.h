#pragma once
namespace pac {
struct vec2 {
  float x, y;
  vec2 operator/(const vec2 &a) { return {x / a.x, y / a.y}; }

  vec2 operator+(const vec2 &a) { return {x + a.x, y + a.y}; }
  vec2 operator-(const vec2 &a) { return {x - a.x, y - a.y}; }
  operator bool() { return x != 0 || y != 0; }
};

struct RigidBody2D {
  virtual ~RigidBody2D() = default;
  RigidBody2D(vec2 _pos) : pos(_pos) {}
  vec2 pos; // center of obj
};
} // namespace pac
