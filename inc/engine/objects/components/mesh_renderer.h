#pragma once

#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/objects/object.h>
#include <memory>

namespace Engine::Objects::Components {
class MeshRenderer : public Component {
 private:
  std::shared_ptr<Assets::Mesh> mesh;
  std::shared_ptr<Assets::Material> material;
  std::shared_ptr<Transform> transform;

 public:
  MeshRenderer(Object& owner) : Component(owner), transform(owner.get_component<Transform>()) {}

  void set_mesh(std::shared_ptr<Assets::Mesh> mesh) { this->mesh = mesh; }
  void set_material(std::shared_ptr<Assets::Material> material) { this->material = material; }

  std::shared_ptr<Assets::Mesh> get_mesh() { return mesh; }
  std::shared_ptr<Assets::Material> get_material() { return material; }

  void start() override;
  void update(double,double delta_time) override;
};
} // namespace Engine::Objects::Components