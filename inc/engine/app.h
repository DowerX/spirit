#pragma once

#include <GLFW/glfw3.h>

namespace Engine {
class App {
 private:
  GLFWwindow* window;

  void process_input();

 public:
  App(uint32_t width, uint32_t height);
  ~App();

  void run();
};

} // namespace Engine