#include "worldentity.h"
#include "simplecollidercomponent.h"
#include "utils.h"
#include <memory>

namespace pac {
WorldEntity::WorldEntity(std::shared_ptr<RigidBody2D> sp) { m_rigidbody = sp; }
int WorldEntity::type() { return pac::NORMAL; }
void WorldEntity::addComponent(Component *component)
// namespace pac
{
  m_components.push_back(std::unique_ptr<pac::Component>(component));
}

const std::shared_ptr<RigidBody2D> WorldEntity::getRigidBody() {
  return m_rigidbody;
}
} // namespace pac
// namespace pac
