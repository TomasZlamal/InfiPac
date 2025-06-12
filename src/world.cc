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

  DEBUG_PRINT("LOOPING")
  entityLoop();
}
void World::addEntity(WorldEntity *entity) { m_entities.push_back(entity); }
void World::handleUserInput(UserInput input) {}
} // namespace pac
