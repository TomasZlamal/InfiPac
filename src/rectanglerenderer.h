#pragma once
#include "renderer.h"

namespace pac {
class RectangleRenderer : public Renderer {
public:
  using Renderer::Renderer;
  void render() const;
};
} // namespace pac
