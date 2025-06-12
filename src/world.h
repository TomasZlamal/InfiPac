#pragma once
#include "collider.h"
#include "simplecollidercomponent.h"
#include "worldentity.h"

#include "debug.h"

#include <vector>
namespace pac {
enum class UserInput { W_KEY, A_KEY, S_KEY, D_KEY };
class World {
  std::vector<WorldEntity *> m_entities;
  void entityLoop();

public:
  World();
  void worldLoop();
  void addEntity(WorldEntity *);
  void handleUserInput(UserInput);
};
} // namespace pac
