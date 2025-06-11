#pragma once
#include "collider.h"
#include "simplecollidercomponent.h"
#include "worldentity.h"

#include "debug.h"

#include <vector>
namespace pac {
class World {
  std::vector<WorldEntity *> m_entities;
  void entityLoop();

public:
  World();
  void worldLoop();
  void addEntity(WorldEntity *);
};
} // namespace pac
