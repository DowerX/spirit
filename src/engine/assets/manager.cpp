#include <engine/assets/manager.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/model.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <memory>

namespace Engine::Assets {

template <>
void Manager::set<Mesh>(const std::string& name, std::shared_ptr<Mesh> asset) {
  meshes[name] = asset;
}
template <>
void Manager::set<Graphics::Shader>(const std::string& name, std::shared_ptr<Graphics::Shader> asset) {
  shaders[name] = asset;
}
template <>
void Manager::set<Texture>(const std::string& name, std::shared_ptr<Texture> asset) {
  textures[name] = asset;
}
template <>
void Manager::set<Material>(const std::string& name, std::shared_ptr<Material> asset) {
  materials[name] = asset;
}
template <>
void Manager::set<Model>(const std::string& name, std::shared_ptr<Model> asset) {
  models[name] = asset;
}

template <>
std::shared_ptr<Mesh> Manager::get<Mesh>(const std::string& name) {
  return meshes[name];
}
template <>
std::shared_ptr<Graphics::Shader> Manager::get<Graphics::Shader>(const std::string& name) {
  return shaders[name];
}
template <>
std::shared_ptr<Texture> Manager::get<Texture>(const std::string& name) {
  return textures[name];
}
template <>
std::shared_ptr<Material> Manager::get<Material>(const std::string& name) {
  return materials[name];
}
template <>
std::shared_ptr<Model> Manager::get<Model>(const std::string& name) {
  return models[name];
}

template <>
void Manager::remove<Mesh>(const std::string& name) {
  meshes.erase(name);
}
template <>
void Manager::remove<Graphics::Shader>(const std::string& name) {
  shaders.erase(name);
}
template <>
void Manager::remove<Texture>(const std::string& name) {
  textures.erase(name);
}
template <>
void Manager::remove<Material>(const std::string& name) {
  materials.erase(name);
}
template <>
void Manager::remove<Model>(const std::string& name) {
  models.erase(name);
}
} // namespace Engine::Assets