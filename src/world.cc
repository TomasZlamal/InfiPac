#include "world.h"
#include <chrono>
#include <thread>
namespace pac {
World::World() {}
void World::entityLoop() {
  for (WorldEntity *entity : m_entities) {
    pac::SimpleColliderComponent *scc =
        entity->getComponent<pac::SimpleColliderComponent>();

    if (scc) {

      for (WorldEntity *entity_b : m_entities) {
        if (entity == entity_b)
          continue;
        Collider *generic_collider = entity_b->getComponent<Collider>();
        if (generic_collider) {
          if (scc->isColliding(generic_collider)) {
            // handle based on types; fruit, ghost, ...
            DEBUG_PRINT("Collided.")
          }
        }
      }
    }
  }
}
void World::worldLoop() {

  while (1) {

    DEBUG_PRINT("LOOPING")
    entityLoop();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
void World::addEntity(WorldEntity *entity) { m_entities.push_back(entity); }
} // namespace pac
