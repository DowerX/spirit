#pragma once

namespace Engine::Assets {
class Drawable {
 public:
  virtual ~Drawable() = default;
  virtual void draw() = 0;
};
} // namespace Engine::Assets