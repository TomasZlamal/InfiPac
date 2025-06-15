#pragma once
#include "debug.h"
namespace pac {
struct vec2 {
  float x, y;
  void abs() {
    if (x < 0)
      x = -x;
    if (y < 0)
      y = -y;
  }
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

} // namespace pac
