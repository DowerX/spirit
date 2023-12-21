#include <engine/objects/components/transform.h>
#include <engine/objects/object.h>
#include <glm/ext/matrix_transform.hpp>
#include <memory>

const glm::vec3 left(1.0f, 0.0f, 0.0f);
const glm::vec3 up(0.0f, 1.0f, 0.0f);
const glm::vec3 forward(0.0f, 0.0f, 1.0f);
const glm::mat4 identity(1.0f);

namespace Engine::Objects::Components {
glm::mat4 Transform::get_parent_matrix() {
  Object* parent = get_owner().get_parent();
  return parent ? parent->get_component<Transform>()->get_transform() : identity;
}

void Transform::set_position(const glm::vec3& position) {
  this->position = position;
  translation_matrix = glm::translate(identity, position);
}

void Transform::set_rotation(const glm::vec3& rotation) {
  this->rotation = rotation;
  rotation_matrix = glm::rotate(identity, glm::radians(rotation.x), left);
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(rotation.y), up);
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(rotation.z), forward);
}
void Transform::set_local_rotation(const glm::vec3& rotation) {
  this->local_rotation = rotation;
  local_rotation_matrix = glm::rotate(identity, glm::radians(rotation.x), left);
  local_rotation_matrix = glm::rotate(local_rotation_matrix, glm::radians(rotation.y), up);
  local_rotation_matrix = glm::rotate(local_rotation_matrix, glm::radians(rotation.z), forward);
}

void Transform::set_scale(const glm::vec3& scale) {
  this->scale = scale;
  scale_matrix = glm::scale(identity, scale);
}

void Transform::translate(const glm::vec3& translation) {
  position += translation;
  set_position(this->position);
}

void Transform::rotate(const glm::vec3& rotation) {
  this->rotation += rotation;
  set_rotation(this->rotation);
}
void Transform::local_rotate(const glm::vec3& rotation) {
  this->local_rotation += rotation;
  set_local_rotation(this->local_rotation);
}

glm::vec3 Transform::get_position() const {
  Object* parent = get_owner().get_parent();
  return (parent ? parent->get_component<Transform>()->get_transform() : identity) * glm::vec4(position, 1.0);
}

} // namespace Engine::Objects::Components