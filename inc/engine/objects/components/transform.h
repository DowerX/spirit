#pragma once

#include <engine/objects/components/component.h>
#include <glm/glm.hpp>

namespace Engine::Objects {
class Object;
}

namespace Engine::Objects::Components {
class Transform : public Component {
 private:
  glm::vec3 position;
  glm::mat4 translation_matrix;

  glm::vec3 rotation;
  glm::mat4 rotation_matrix;

  glm::vec3 local_rotation;
  glm::mat4 local_rotation_matrix;

  glm::vec3 scale;
  glm::mat4 scale_matrix;

  glm::mat4 get_parent_matrix();

 public:
  Transform(Object& owner, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& local_rotation, const glm::vec3 scale) : Component(owner) {
    set_position(position);
    set_rotation(rotation);
    set_local_rotation(local_rotation);
    set_scale(scale);
  }
  Transform(Object& owner)
      : Transform(owner, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)) {}

  void set_position(const glm::vec3& position);

  void set_rotation(const glm::vec3& rotation);
  void set_local_rotation(const glm::vec3& local_rotation);

  void set_scale(const glm::vec3& scale);

  void translate(const glm::vec3& translation);

  void rotate(const glm::vec3& rotation);
  void local_rotate(const glm::vec3& rotation);

  glm::vec3 get_position() const;
  glm::vec3 get_local_position() const { return position; }

  glm::vec3 get_rotation() const { return rotation; }
  glm::vec3 get_local_rotation() const { return local_rotation; }

  glm::vec3 get_scale() const { return scale; }

  glm::mat4 get_transform() { return get_parent_matrix() * local_rotation_matrix * translation_matrix * rotation_matrix * scale_matrix; }
};

} // namespace Engine::Objects::Components