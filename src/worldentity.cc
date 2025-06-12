#include "worldentity.h"
#include "simplecollidercomponent.h"

namespace pac {

void WorldEntity::tick() {}
void WorldEntity::addComponent(Component *component)
// namespace pac
{
  m_components.push_back(component);
}

const std::shared_ptr<RigidBody2D> WorldEntity::getRigidBody() {
  return m_rigidbody;
}
} // namespace pac
// namespace pac
