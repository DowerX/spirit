#include <engine/app.h>
#include <engine/assets/manager.h>
#include <engine/objects/components/light.h>
#include <cstddef>
#include <memory>
#include <string>
#include <engine/objects/components/transform.h>
#include <engine/utility.h>

using namespace Engine::Graphics;

namespace Engine::Objects::Components {

void Light::start() {
  transform = get_owner().get_component<Transform>();
}

void Light::early_update(double, double) {
  static Assets::Manager& manager = App::get_instance().get_asset_manager();

  size_t index = manager.get_light_index();
  std::string element("lights[" + std::to_string(index) + "]");

  for (auto& shader : manager.get_all<Shader>()) {
    shader.second->use();
    shader.second->set<glm::vec3>(element + ".color", color);
    shader.second->set<glm::vec3>(element + ".position", transform->get_translation());
    shader.second->set<int>(element + ".type", type);
    shader.second->set<int>("light_count", index + 1);
  }
}

} // namespace Engine::Objects::Components