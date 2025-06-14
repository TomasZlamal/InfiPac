#include "gravitycomponent.h"

namespace pac {

vec2 GravityComponent::getMove() { return m_g * m_rb->weight; }
} // namespace pac
