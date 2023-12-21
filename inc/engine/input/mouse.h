#pragma once

namespace Engine::Input {
class Mouse {
 private:
  double x;
  double y;

  double x_relative;
  double y_relative;

  Mouse() : x(0), y(0), x_relative(0), y_relative(0){};

 public:
  Mouse(const Mouse&) = delete;
  void operator=(const Mouse&) = delete;

  static Mouse& get_instance();

  static void mouse_callback(double x, double y);
  static void mouse_relative_reset();

  double get_x() { return x; }
  double get_y() { return y; }
  double get_x_relative() { return x_relative; }
  double get_y_relative() { return y_relative; }
};
} // namespace Engine::Input