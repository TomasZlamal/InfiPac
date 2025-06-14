#pragma once
#include "component.h"
#include "rigidbody.h"

#include "libs/raylib/src/raylib.h"

#include <memory>
namespace pac {
class Renderer : public Component {
protected:
  std::shared_ptr<RigidBody2D> m_rigidbody;
  Color m_color;

public:
  Renderer(std::shared_ptr<RigidBody2D> rb) : m_rigidbody(rb), m_color(RED) {}
  Renderer(std::shared_ptr<RigidBody2D> rb, Color color)
      : m_rigidbody(rb), m_color(color) {}
  virtual void render() const = 0;
};

} // namespace pac
