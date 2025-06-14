#pragma once
#include "component.h"
#include "math_structs.h"
#include "worldentity.h"
#include <vector>
namespace pac {
class SimpleAIComponent : public Component {

  std::shared_ptr<RigidBody2D> m_rb;

  float m_anger = 1.0f;
  float m_maxanger = 8.0f;

public:
  SimpleAIComponent(std::shared_ptr<RigidBody2D> rb) : m_rb(rb) {}
  vec2 getMove(const std::vector<WorldEntity *> &m_entities);
  void add_anger(float factor);
  void set_max_anger(float max);
};
} // namespace pac
