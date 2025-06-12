#include "src/collider.h"
#include "src/debug.h"
#include "src/playercomponent.h"
#include "src/rectanglerenderer.h"
#include "src/simplecollidercomponent.h"
#include "src/world.h"
#include "src/worldentity.h"
#include <memory>

int main() {
  pac::World world;
  world.runWorld();
  DEBUG_PRINT("end")
  return 0;
}
