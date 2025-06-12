#pragma once
#include "simplecollidercomponent.h"
#include <memory>
#include <vector>
namespace pac {

class Component;
class WorldEntity {
  std::vector<Component *> m_components;
  std::shared_ptr<RigidBody2D> m_rigidbody;

public:
  void tick();
  template <typename T> T *getComponent() {
    for (pac::Component *component : m_components) {
      if (dynamic_cast<T *>(component)) {
        return dynamic_cast<T *>(component);
      }
    }
    return 0;
  }
  /*
  Usage with WorldEntity:
  ```
  pac::WorldEntity we;
  we.addComponent(new pac::SimpleColliderComponent());
  pac::SimpleColliderComponent *scc =
  we.getComponent<pac::SimpleColliderComponent>();
  if (scc) {
  scc->collisionLogic();
  }
  ```
  */
  void addComponent(Component *component);
  const std::shared_ptr<RigidBody2D> getRigidBody();
};
} // namespace pac
