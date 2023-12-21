#pragma once

#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <engine/objects/object.h>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace Engine::Assets {
class Manager {
 private:
  std::shared_ptr<Objects::Object> root_object;

  size_t light_index;

  std::map<std::string, std::shared_ptr<Material>> materials;
  std::map<std::string, std::shared_ptr<Texture>> textures;
  std::map<std::string, std::shared_ptr<Graphics::Shader>> shaders;
  std::map<std::string, std::shared_ptr<Mesh>> meshes;

 public:
  Manager() : root_object(new Objects::Object()), light_index(0) {}

  std::shared_ptr<Objects::Object> get_root_object() { return root_object; }

  size_t get_light_index() { return light_index++; }
  void reset_light_index() { light_index = 0; }

  template <typename T>
  void set(const std::string& name, std::shared_ptr<T> asset);

  template <typename T>
  std::shared_ptr<T> get(const std::string& name);

  template <typename T>
  std::map<std::string, std::shared_ptr<T>>& get_all();

  template <typename T>
  void remove(const std::string& name);
};

} // namespace Engine::Assets