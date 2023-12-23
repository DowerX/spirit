#include <GLFW/glfw3.h>
#include <engine/input/keyboard.h>
#include <engine/input/mouse.h>
#include <game/camera_controller.h>
#include <glm/glm.hpp>

using namespace Engine::Input::Keyboard;
using namespace Engine::Input;
using namespace Engine::Objects::Components;

void CameraController::start() {
  transform = get_owner().get_component<Transform>();
}

void CameraController::update(double, double delta_time) {
  static Mouse& mouse = Mouse::get_instance();

  glm::vec3 look(0.0f);
  look.x = -mouse.get_y_relative();
  look.y = -mouse.get_x_relative();
  transform->local_rotate(look * sensitivity * (float)delta_time);

  // transform->translate((
  //   ((float)get_key(GLFW_KEY_A) - (float)get_key(GLFW_KEY_D))*transform->get_left()+
  //   ((float)get_key(GLFW_KEY_SPACE) - (float)get_key(GLFW_KEY_LEFT_SHIFT))*transform->get_up()+
  //   ((float)get_key(GLFW_KEY_W) - (float)get_key(GLFW_KEY_S))*transform->get_forward()
  // ) * (float)delta_time * speed);
  transform->local_translate(glm::vec3(
    ((float)get_key(GLFW_KEY_A) - (float)get_key(GLFW_KEY_D)),
    ((float)get_key(GLFW_KEY_SPACE) - (float)get_key(GLFW_KEY_LEFT_SHIFT)),
    ((float)get_key(GLFW_KEY_W) - (float)get_key(GLFW_KEY_S))
  ) * (float)delta_time * speed);
}