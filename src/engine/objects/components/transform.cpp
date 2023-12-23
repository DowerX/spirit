#include <engine/objects/components/transform.h>
#include <engine/objects/object.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

const glm::vec3 world_left(1, 0, 0);
const glm::vec3 world_up(0, 1, 0);
const glm::vec3 world_forward(0, 0, 1);
const glm::mat4 identity(glm::identity<glm::mat4>());

namespace Engine::Objects::Components {
void Transform::start() {
  calculate();
}

glm::mat4 Transform::get_parent_transform() const {
  Object* parent = get_owner().get_parent();
  return parent ? parent->get_component<Transform>()->get_transform() : identity;
}

void Transform::calculate() {
  global_transform = get_parent_transform();

  global_transform = glm::rotate(global_transform, glm::radians(local_rotation.x), world_left);
  global_transform = glm::rotate(global_transform, glm::radians(local_rotation.y), world_up);
  global_transform = glm::rotate(global_transform, glm::radians(local_rotation.z), world_forward);

  global_transform = glm::translate(global_transform, local_translation);
  global_transform = glm::scale(global_transform, local_scale);
  decompose();

  glm::mat4 inverted = glm::inverse(global_transform);
  forward = normalize(glm::vec3(inverted[2]));
  left = normalize(glm::vec3(inverted[0]));
  up = normalize(glm::cross(glm::vec3(inverted[0]), glm::vec3(inverted[2])));
}

void Transform::decompose() {
  glm::quat global_rotation_quat;
  glm::vec3 skew;
  glm::vec4 perspective;

  glm::decompose(global_transform, global_scale, global_rotation_quat, global_translation, skew, perspective);

  global_rotation = glm::degrees(glm::eulerAngles(global_rotation_quat));
}

void Transform::translate(const glm::vec3& translation) {
  local_translation += translation;
  calculate();
}

void Transform::local_translate(const glm::vec3& translation) {
  glm::vec3 rel = get_left()*translation.x + get_up()* translation.y + get_forward() * translation.z;
  local_translation += rel;
  calculate();
}

void Transform::local_rotate(const glm::vec3& rotation) {
  local_rotation += rotation;
  calculate();
};
} // namespace Engine::Objects::Components