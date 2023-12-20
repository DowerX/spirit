#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/assets/loaders/obj.h>
#include <engine/assets/loaders/png.h>
#include <engine/assets/manager.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <engine/objects/components/mesh_renderer.h>
#include <engine/objects/object.h>
#include <engine/utility.h>
#include <game/rotator_component.h>
#include <exception>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Engine;
using namespace Engine::Assets;
using namespace Engine::Graphics;
using namespace Engine::Objects;
using namespace Engine::Objects::Components;
using namespace Engine::Utility;

int main() {
  std::unique_ptr<App> app;
  try {
    app = std::make_unique<App>(800, 600);
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  Manager& assets = app->get_asset_manager();

  // load assets
  try {
    assets.set<Shader>("basic", Shader::from_file("assets/shaders/basic/basic.vert", "assets/shaders/basic/basic.frag"));

    assets.set<Mesh>("cube", Loaders::obj("assets/meshes/cube/cube.obj"));
    assets.set<Mesh>("suzanne", Loaders::obj("assets/meshes/suzanne/suzanne.obj"));

    assets.set<Texture>("rloi_mc", Loaders::png("assets/textures/cube.png"));

    assets.set<Material>("basic_rloi", std::make_shared<Material>(assets.get<Shader>("basic"), std::vector<TextureSlot>{{0, assets.get<Texture>("rloi_mc")}}));

    auto cube = assets.get_root_object()->add_child("cube");
    auto cube_mesh_renderer = cube->add_component<MeshRenderer>();
    cube_mesh_renderer->set_mesh(assets.get<Mesh>("cube"));
    cube_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto cube_transform = cube->get_component<Transform>();
    cube_transform->translate(glm::vec3(0.0f, 0.0f, 0.0f));
    cube->add_component<Rotator>();

    auto suzanne = cube->add_child("suzanne");
    auto suzanne_mesh_renderer = suzanne->add_component<MeshRenderer>();
    suzanne_mesh_renderer->set_mesh(assets.get<Mesh>("suzanne"));
    suzanne_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto suzanne_transform = suzanne->get_component<Transform>();
    suzanne_transform->set_position(glm::vec3(3.0f, 0.0f, 0.0f));
    suzanne->add_component<Rotator>();
    suzanne->get_component<Rotator>()->set_scale(10);

    auto shader = assets.get<Shader>("basic");
    // gameloop
    app->run([&]() {
      shader->use();
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f));
      glm::mat4 proj = glm::perspective(glm::radians(75.0f), app->get_aspect_ratio(), 0.001f, 100.0f);
      shader->set<glm::mat4>("view", view);
      shader->set<glm::mat4>("projection", proj);
    });
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}