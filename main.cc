#include "src/world.h"
#include <memory>

int main() {
  pac::World world{500, 500};
  world.runWorld();
  return 0;
}
