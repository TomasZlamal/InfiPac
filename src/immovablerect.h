#pragma once

#include "worldentity.h"
namespace pac {
class ImmovableRect : public WorldEntity {
public:
  ImmovableRect(vec2, vec2);
};
} // namespace pac
