#pragma once

#include <engine/objects/components/component.h>
#include <glm/common.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <memory>

namespace Engine::Objects {
class Object;
}

namespace Engine::Objects::Components {
class Transform : public Component {
 private:
  glm::mat4 get_parent_transform() const;
  void decompose();
  void calculate();

  glm::vec3 local_translation;
  glm::vec3 local_rotation;
  glm::vec3 local_scale;

  glm::vec3 global_translation;
  glm::vec3 global_rotation;
  glm::vec3 global_scale;

  glm::mat4 global_transform;

  glm::vec3 left;
  glm::vec3 up;
  glm::vec3 forward;

 public:
  Transform() : local_translation(0.0f), local_rotation(0.0f), local_scale(1.0f) { }

  void set_local_translation(const glm::vec3& value) {
    local_translation = value;
    calculate();
  }
  void set_local_rotation(const glm::vec3& value) {
    local_rotation = value;
    calculate();
  }
  void set_local_scale(const glm::vec3& value) {
    local_scale = value;
    calculate();
  }

  const glm::vec3& get_local_translation() const { return local_translation; }
  const glm::vec3& get_local_rotation() const { return local_rotation; }
  const glm::vec3& get_local_scale() const { return local_scale; }

  const glm::vec3& get_translation() const { return global_translation; }
  const glm::vec3& get_rotation() const { return global_rotation; }
  const glm::vec3& get_scale() const { return global_scale; }

  const glm::mat4& get_transform() const { return global_transform; };

  glm::vec3 get_forward() const { return forward; }
  glm::vec3 get_left() const { return left; };
  glm::vec3 get_up() const { return up; }

  void local_rotate(const glm::vec3& rotation);

  void translate(const glm::vec3& translate);
  void local_translate(const glm::vec3& translate);

  void start() override;
};

} // namespace Engine::Objects::Components