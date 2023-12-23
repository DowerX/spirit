#pragma once

#include <engine/graphics/shader.h>
#include <engine/objects/object.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>

namespace Engine::Objects::Components {
class Light : public Component {
 public:
  enum Type : int { POINT = 0, SPOT, AMBIENT };

  Light() : type(POINT), color(glm::vec3(1.0f)) {}

  void set_type(Type type) { this->type = type; };
  void set_color(const glm::vec3& color) { this->color = color; };

  void start() override;
  void early_update(double, double) override;

 private:
  Type type;
  glm::vec3 color;
  std::shared_ptr<Objects::Components::Transform> transform;
};
} // namespace Engine::Objects::Components