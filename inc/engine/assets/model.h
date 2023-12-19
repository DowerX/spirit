#pragma once

#include <engine/assets/drawable.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <memory>

namespace Engine::Assets {
class Model : public Drawable {
 private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;

 public:
  Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : mesh(mesh), material(material) {}

  std::shared_ptr<Mesh> get_mesh() const { return mesh; }
  std::shared_ptr<Material> get_material() const { return material; }

  void draw() override;
};

} // namespace Engine::Assets::Objects