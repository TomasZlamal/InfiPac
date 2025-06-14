#include "simpleaicomponent.h"
#include "debug.h"
#include "playercomponent.h"
#include <cstdlib>
namespace pac {
vec2 SimpleAIComponent::getMove(const std::vector<WorldEntity *> &m_entities) {
  for (auto entity : m_entities) {
    if (entity->getComponent<PlayerComponent>()) {
      vec2 temp = entity->getRigidBody()->pos - m_rb->pos;
      if ((rand() % 50) > 48) {
        return temp / ((float)(rand() % 12) + 6.0f); //- vec2{50, 50};
      }
      float total = std::abs(temp.x) + std::abs(temp.y);
      return vec2{temp.x / total, temp.y / total} / 2.0f * m_anger;
    }
  }
  return {};
}

void SimpleAIComponent::add_anger(float factor) {

  m_anger += factor;
  if ((rand() % 100000) > 99995) {
    m_anger = m_maxanger - factor / 180;
  }
  if (m_anger > m_maxanger) {
    m_anger = 1.0f;
  }
}

void SimpleAIComponent::set_max_anger(float max) { m_maxanger = max; }
} // namespace pac
