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
#include <type_traits>

namespace Engine::Assets {
class Manager {
 private:
  std::shared_ptr<Objects::Object> root_object;

  size_t light_index;

  std::map<std::string, std::shared_ptr<Material>> materials;
  std::map<std::string, std::shared_ptr<Texture>> textures;
  std::map<std::string, std::shared_ptr<Graphics::Shader>> shaders;
  std::map<std::string, std::shared_ptr<Mesh>> meshes;

  template <typename T>
  struct is_asset_type {
    static constexpr bool value =
      std::is_base_of<Material, T>::value ||
      std::is_base_of<Texture, T>::value ||
      std::is_base_of<Graphics::Shader, T>::value ||
      std::is_base_of<Mesh, T>::value;
  };

 public:
  Manager() : root_object(new Objects::Object()), light_index(0) {}

  std::shared_ptr<Objects::Object> get_root_object() { return root_object; }

  size_t get_light_index() { return light_index++; }
  void reset_light_index() { light_index = 0; }

  template <typename T, typename = typename std::enable_if<is_asset_type<T>::value>::type>
  void set(const std::string& name, std::shared_ptr<T> asset);

  template <typename T, typename = typename std::enable_if<is_asset_type<T>::value>::type>
  std::shared_ptr<T> get(const std::string& name);

  template <typename T, typename = typename std::enable_if<is_asset_type<T>::value>::type>
  std::map<std::string, std::shared_ptr<T>>& get_all();

  template <typename T, typename = typename std::enable_if<is_asset_type<T>::value>::type>
  void remove(const std::string& name);
};

} // namespace Engine::Assets