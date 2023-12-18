#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include "engine/assets/mesh.h"

namespace Engine {
class App {
 private:
  GLFWwindow* window;
  uint32_t width;
  uint32_t height;

  void process_input();

 public:
  App(uint32_t width, uint32_t height);
  ~App();

  uint32_t get_width() const { return width; }
  uint32_t get_height() const { return height; }
  float get_aspect_ratio() const { return (float)width / height; }

  void run(const std::function<void()>& loop);
};

} // namespace Engine