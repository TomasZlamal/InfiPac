#pragma once
#include "libs/raylib/src/raylib.h"

#include "collider.h"
#include "simplecollidercomponent.h"
#include "worldentity.h"

#include "debug.h"

#include <queue>
#include <vector>
namespace pac {
enum class UserInput { W_KEY, A_KEY, S_KEY, D_KEY, SPACE_KEY };
class World {
  std::vector<WorldEntity *> m_entities;
  void entityLoop();
  std::queue<UserInput> m_inputs;
  vec2 posLocation(vec2 rb);
  void tryMoveRigidBody(std::shared_ptr<RigidBody2D> rb, vec2 factor);
  int m_screenheight;
  int m_screenwidth;
  int m_score;

public:
  World(int, int);
  void runWorld();
  void worldLoop();
  void addEntity(WorldEntity *);
  void handleUserInput(UserInput);
};
} // namespace pac
