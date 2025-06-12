#include "rectanglerenderer.h"
#include "debug.h"
#include "simplecollidercomponent.h"

namespace pac {
void RectangleRenderer::render() const {
  auto rrb = dynamic_cast<RectangleRigidBody *>(m_rigidbody.get());
  DrawRectangle(rrb->pos.x, rrb->pos.y, rrb->wh.x, rrb->wh.y,
                (Color){230, 41, 55, 255});
}
} // namespace pac
