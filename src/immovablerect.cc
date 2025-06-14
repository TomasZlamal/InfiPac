#include "immovablerect.h"
#include "libs/raylib/src/raylib.h"
#include "rectanglerenderer.h"
#include "simplecollidercomponent.h"
#include "utils.h"
#include "worldentity.h"
#include <filesystem>

namespace pac {
ImmovableRect::ImmovableRect(vec2 wh, vec2 pos)
    : WorldEntity(std::shared_ptr<pac::RectangleRigidBody>(
          new pac::RectangleRigidBody({wh, pos, 10000000000}))) {
  addComponent(new SimpleColliderComponent(m_rigidbody));
  addComponent(new RectangleRenderer(m_rigidbody, PURPLE));
}

ImmovableRect::ImmovableRect(vec2 wh, vec2 pos, Color color)
    : WorldEntity(std::shared_ptr<pac::RectangleRigidBody>(
          new pac::RectangleRigidBody({wh, pos, 10000000000}))) {
  addComponent(new SimpleColliderComponent(m_rigidbody));
  addComponent(new RectangleRenderer(m_rigidbody, color));
}

int ImmovableRect::type() { return IMMOVABLE_RECT; }
} // namespace pac
