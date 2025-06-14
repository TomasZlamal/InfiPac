#pragma once
#include "component.h"
#include "rigidbody.h"
#include <memory>
namespace pac {
class GravityComponent : public Component {
  vec2 m_g;
  std::shared_ptr<RigidBody2D> m_rb;

public:
  GravityComponent(std::shared_ptr<RigidBody2D> rb, vec2 g)
      : m_rb(rb), m_g(g) {}
  vec2 getMove();
  void setGravity(vec2);
};
} // namespace pac
