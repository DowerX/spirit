#pragma once

#include <engine/assets/drawable.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace Engine::Assets {
class Model : public Drawable {
 private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::mat4 transform_matrix;

  void set_transform_matrix();

 public:
  Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

  void set_position(const glm::vec3& position);
  void set_rotation(const glm::vec3& rotation);
  void set_scale(const glm::vec3& scale);

  void translate(const glm::vec3& translation);

  void rotate(const glm::vec3& rotation);

  glm::vec3 get_position() const { return position; }
  glm::vec3 get_rotation() const { return rotation; }
  glm::vec3 get_scale() const { return scale; }

  std::shared_ptr<Mesh> get_mesh() const { return mesh; }
  std::shared_ptr<Material> get_material() const { return material; }

  void draw() override;
};

} // namespace Engine::Assets