#include <engine/objects/object.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>

const glm::vec3 left(1.0f, 0.0f, 0.0f);
const glm::vec3 up(0.0f, 1.0f, 0.0f);
const glm::vec3 forward(0.0f, 0.0f, 1.0f);
const glm::mat4 identity(1.0f);

namespace Engine::Objects::Components {
void Transform::set_transform_matrix() {
  Object* parent = get_owner().get_parent();
  transform_matrix = parent ? parent->get_component<Transform>()->get_transform() : identity;
  transform_matrix = glm::translate(transform_matrix, position);
  transform_matrix = glm::scale(transform_matrix, scale);

  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.x), left);
  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.y), up);
  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.z), forward);

  for (auto child : get_owner().get_children()) {
    child.second->get_component<Transform>()->set_transform_matrix();
  }
}

void Transform::set_position(const glm::vec3& position) {
  this->position = position;
  set_transform_matrix();
}
void Transform::set_rotation(const glm::vec3& rotation) {
  this->rotation = rotation;
  set_transform_matrix();
}
void Transform::set_scale(const glm::vec3& scale) {
  this->scale = scale;
  set_transform_matrix();
}

void Transform::translate(const glm::vec3& translation) {
  position += translation;
  set_transform_matrix();
}
void Transform::rotate(const glm::vec3& rotation) {
  this->rotation += rotation;
  set_transform_matrix();
}

} // namespace Engine::Objects::Components