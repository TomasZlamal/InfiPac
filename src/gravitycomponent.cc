#include "gravitycomponent.h"

namespace pac {

vec2 GravityComponent::getMove() { return m_g * m_rb->weight; }

void GravityComponent::setGravity(vec2 v) { m_g = v; }
} // namespace pac
