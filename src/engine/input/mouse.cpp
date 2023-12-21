#include <engine/input/mouse.h>

namespace Engine::Input {
Mouse& Mouse::get_instance() {
  static Mouse mouse;
  return mouse;
}

void Mouse::mouse_callback(double x, double y) {
  static Mouse& mouse = get_instance();
  mouse.x_relative = mouse.x - x;
  mouse.y_relative = mouse.y - y;
  mouse.x = x;
  mouse.y = y;
}

void Mouse::mouse_relative_reset() {
  static Mouse& mouse = get_instance();
  mouse.x_relative = 0;
  mouse.y_relative = 0;
}
} // namespace Engine::Input