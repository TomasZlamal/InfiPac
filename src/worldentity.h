#pragma once
#include <vector>
namespace pac {

class Component;
class WorldEntity {
  std::vector<Component *> m_components;

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
  void addComponent(Component *component) { m_components.push_back(component); }
};
} // namespace pac
