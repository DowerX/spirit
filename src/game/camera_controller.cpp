#include <GLFW/glfw3.h>
#include <engine/input/keyboard.h>
#include <engine/input/mouse.h>
#include <game/camera_controller.h>
#include <glm/glm.hpp>

using namespace Engine::Input::Keyboard;
using namespace Engine::Input;

void CameraController::update(double, double delta_time) {
  static Mouse& mouse = Mouse::get_instance();

  glm::vec3 look(0.0f);
  look.x = -mouse.get_y_relative();
  look.y = -mouse.get_x_relative();
  transform->local_rotate(look * sensitivity * (float)delta_time);

  float yaw = transform->get_local_rotation().y + 90;
  float pitch = transform->get_local_rotation().x;

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(front);

  glm::vec3 left(front.z, 0.0, -front.x);

  transform->translate(
      (front * ((float)get_key(GLFW_KEY_W) + -(float)get_key(GLFW_KEY_S)) + left * ((float)get_key(GLFW_KEY_A) + -(float)get_key(GLFW_KEY_D))) * speed *
      (float)delta_time);
}