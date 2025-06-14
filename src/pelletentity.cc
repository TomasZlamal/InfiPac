#include "pelletentity.h"
#include "pelletcomponent.h"
#include "rectanglerenderer.h"
#include "worldentity.h"

namespace pac {

PelletEntity::PelletEntity(vec2 wh, vec2 pos)
    : WorldEntity(std::shared_ptr<pac::RectangleRigidBody>(
          new pac::RectangleRigidBody({wh, pos, 1}))) {
  addComponent(new SimpleColliderComponent(m_rigidbody));
  addComponent(new RectangleRenderer(m_rigidbody, WHITE));
  addComponent(new PelletComponent());
}
} // namespace pac
