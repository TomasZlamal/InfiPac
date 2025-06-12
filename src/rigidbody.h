#pragma once
struct vec2 {
  float x, y;
  vec2 operator/(const vec2 &a) { return {x / a.x, y / a.y}; }

  vec2 operator+(const vec2 &a) { return {x + a.x, y + a.y}; }
  vec2 operator-(const vec2 &a) { return {x - a.x, y - a.y}; }
};

struct RigidBody2D {
  RigidBody2D(vec2 _pos) : pos(_pos) {}
  vec2 pos; // center of obj
};
