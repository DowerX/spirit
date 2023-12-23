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
#include <engine/objects/components/light.h>
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
#include <engine/objects/components/transform.h>

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
    assets.set<Mesh>("sponza", Loaders::obj("assets/meshes/sponza/sponza.obj"));

    assets.set<Texture>("rloi_mc", Loaders::png("assets/textures/cube.png"));
    assets.set<Texture>("sponza", Loaders::png("assets/textures/sponza.png"));

    assets.set<Material>("basic_rloi", std::make_shared<Material>(assets.get<Shader>("basic"), std::vector<TextureSlot>{{0, assets.get<Texture>("rloi_mc")}}));
    assets.set<Material>("basic_sponza", std::make_shared<Material>(assets.get<Shader>("basic"), std::vector<TextureSlot>{{0, assets.get<Texture>("sponza")}}));

    assets.get<Material>("basic_sponza")->set_shininess(1);

    auto root_object = assets.get_root_object();

    auto light = root_object->add_child("light");
    light->get_component<Transform>()->set_local_translation(glm::vec3(0.0, 0.0, 0.3));
    auto light_component = light->add_component<Light>();

    auto camera = root_object->add_child("camera");
    auto camera_transform = camera->get_component<Transform>();
    camera_transform->set_local_translation(glm::vec3(0.0f, 0.0f, -0.3f));
    camera->add_component<Camera>();
    camera->add_component<CameraController>();
    // camera->add_component<Light>();

    auto sponza = root_object->add_child("sponza");
    auto sponza_mesh_renderer = sponza->add_component<MeshRenderer>();
    sponza_mesh_renderer->set_mesh(assets.get<Mesh>("sponza"));
    sponza_mesh_renderer->set_material(assets.get<Material>("basic_sponza"));
    sponza->get_component<Transform>()->set_local_scale(glm::vec3(0.5));

    auto cube = root_object->add_child("cube");
    auto cube_mesh_renderer = cube->add_component<MeshRenderer>();
    cube_mesh_renderer->set_mesh(assets.get<Mesh>("cube"));
    cube_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto cube_transform = cube->get_component<Transform>();
    cube_transform->set_local_scale(glm::vec3(0.1f));
    cube->add_component<Rotator>();

    auto suzanne = cube->add_child("suzanne");
    auto suzanne_mesh_renderer = suzanne->add_component<MeshRenderer>();
    suzanne_mesh_renderer->set_mesh(assets.get<Mesh>("suzanne"));
    suzanne_mesh_renderer->set_material(assets.get<Material>("basic_rloi"));
    auto suzanne_transform = suzanne->get_component<Transform>();
    suzanne_transform->set_local_translation(glm::vec3(6.0f, 0.0f, 0.0f));
    suzanne->add_component<Rotator>();
    suzanne->get_component<Rotator>()->set_scale(10);
    suzanne->add_component<Light>();
    suzanne->get_component<Light>()->set_color(glm::vec3(1, 0, 0));

    App::get_instance().run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}