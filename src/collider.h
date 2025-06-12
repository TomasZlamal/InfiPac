#pragma once
#include "component.h"
#include "rigidbody.h"
#include <memory>
namespace pac {
// owns the collision logic for the entity; also owns the location data +
// measurments
class Collider : public Component {
protected:
  std::shared_ptr<RigidBody2D> m_rigidbody;

public:
  Collider(std::shared_ptr<RigidBody2D> sptr) : m_rigidbody(sptr) {}
  virtual vec2 isColliding(Collider *) = 0;
  std::shared_ptr<RigidBody2D> getRigidBody() { return m_rigidbody; }
};
} // namespace pac
