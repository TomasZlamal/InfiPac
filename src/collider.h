#pragma once
#include "component.h"
namespace pac {
// owns the collision logic for the entity; also owns the location data +
// measurments
class Collider : public Component {
public:
  virtual bool isColliding(Collider *) = 0;
};
} // namespace pac
