#pragma once

#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/model.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace Engine::Assets {
class Manager {
 private:
  std::map<std::string, std::shared_ptr<Model>> models;
  std::map<std::string, std::shared_ptr<Material>> materials;
  std::map<std::string, std::shared_ptr<Texture>> textures;
  std::map<std::string, std::shared_ptr<Graphics::Shader>> shaders;
  std::map<std::string, std::shared_ptr<Mesh>> meshes;

 public:
  template <typename T>
  void set(const std::string& name, std::shared_ptr<T> asset);

  template <typename T>
  std::shared_ptr<T> get(const std::string& name);

  template <typename T>
  void remove(const std::string& name);
};

} // namespace Engine::Assets