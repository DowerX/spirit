#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/assets/loaders/obj.h>
#include <engine/assets/loaders/png.h>
#include <engine/assets/manager.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <engine/objects/components/camera.h>
#include <engine/objects/components/mesh_renderer.h>
#include <engine/objects/object.h>
#include <engine/utility.h>
#include <game/camera_controller.h>
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
  App::initialize(App::Config());

  Manager& assets = App::get_instance().get_asset_manager();

  // load assets
  try {
    assets.set<Shader>("basic", Shader::from_file("assets/shaders/basic/basic.vert", "assets/shaders/basic/basic.frag"));

    assets.set<Mesh>("cube", Loaders::obj("assets/meshes/cube/cube.obj"));
    assets.set<Mesh>("suzanne", Loaders::obj("assets/meshes/suzanne/suzanne.obj"));
    assets.set<Mesh>("plane", Loaders::obj("assets/meshes/plane/plane.obj"));

    assets.set<Texture>("rloi_mc", Loaders::png("assets/textures/cube.png"));

    assets.set<Material>("basic_rloi", std::make_shared<Material>(assets.get<Shader>("basic"), std::vector<TextureSlot>{{0, assets.get<Texture>("rloi_mc")}}));

    auto camera = assets.get_root_object()->add_child("camera");
    auto camera_transform = camera->get_component<Transform>();
    camera_transform->set_position(glm::vec3(0.0f, 0.0f, -0.3f));
    camera->add_component<Camera>();
    camera->add_component<CameraController>();

    auto plane = assets.get_root_object()->add_child("plane");
    auto plane_mesh_renderer = plane->add_component<MeshRenderer>();
    plane_mesh_renderer->set_mesh(assets.get<Mesh>("plane"));
    plane_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto plane_transform = plane->get_component<Transform>();
    plane_transform->translate(glm::vec3(0, -0.2, 0));

    auto cube = assets.get_root_object()->add_child("cube");
    auto cube_mesh_renderer = cube->add_component<MeshRenderer>();
    cube_mesh_renderer->set_mesh(assets.get<Mesh>("cube"));
    cube_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto cube_transform = cube->get_component<Transform>();
    cube_transform->set_scale(glm::vec3(0.1f));
    cube->add_component<Rotator>();

    auto suzanne = cube->add_child("suzanne");
    auto suzanne_mesh_renderer = suzanne->add_component<MeshRenderer>();
    suzanne_mesh_renderer->set_mesh(assets.get<Mesh>("suzanne"));
    suzanne_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto suzanne_transform = suzanne->get_component<Transform>();
    suzanne_transform->set_position(glm::vec3(3.0f, 0.0f, 0.0f));
    suzanne->add_component<Rotator>();
    suzanne->get_component<Rotator>()->set_scale(10);

    App::get_instance().run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}