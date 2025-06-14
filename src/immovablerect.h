#pragma once

#include "libs/raylib/src/raylib.h"
#include "worldentity.h"
namespace pac {
class ImmovableRect : public WorldEntity {
public:
  ImmovableRect(vec2, vec2);
  ImmovableRect(vec2, vec2, Color);
  int type();
};
} // namespace pac
