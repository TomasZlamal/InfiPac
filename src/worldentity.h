#pragma once
#include "debug.h"
#include "simplecollidercomponent.h"
#include <memory>
#include <optional>
#include <vector>
namespace pac {

class WorldEntity {
  std::vector<std::unique_ptr<Component>> m_components;

protected:
  std::shared_ptr<RigidBody2D> m_rigidbody;

public:
  WorldEntity(std::shared_ptr<RigidBody2D>);
  virtual int type();
  template <typename T> T *getComponent() {
    for (auto &component : m_components) {
      auto comp_pointer = component.get();

      if (dynamic_cast<T *>(comp_pointer)) {
        return dynamic_cast<T *>(comp_pointer);
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
