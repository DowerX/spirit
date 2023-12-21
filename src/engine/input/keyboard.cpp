#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/input/keyboard.h>

namespace Engine::Input::Keyboard {

bool get_key(int key) {
  static GLFWwindow* window = App::get_instance().get_window();
  switch (glfwGetKey(window, key)) {
    case GLFW_PRESS:
      return true;
    case GLFW_RELEASE:
    default:
      return false;
  }
}
} // namespace Engine::Input::Keyboard