#include <engine/app.h>
#include <engine/assets/loaders/obj.h>
#include <engine/assets/loaders/png.h>
#include <engine/assets/manager.h>
#include <engine/assets/material.h>
#include <engine/assets/mesh.h>
#include <engine/assets/model.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <engine/utility.h>
#include <exception>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Engine;
using namespace Engine::Assets;
using namespace Engine::Graphics;
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
    assets.set<Texture>("rloi_mc", Loaders::png("assets/textures/cube.png"));
    assets.set<Material>("basic_rloi", std::make_shared<Material>(assets.get<Shader>("basic"), std::vector<TextureSlot>{{0, assets.get<Texture>("rloi_mc")}}));

    assets.set<Model>("cube", std::make_shared<Model>(assets.get<Mesh>("cube"), assets.get<Material>("basic_rloi")));

    // gameloop
    app->run([&]() {
      auto shader = assets.get<Shader>("basic");
      shader->use();
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f));
      glm::mat4 proj = glm::perspective(glm::radians(75.0f), app->get_aspect_ratio(), 0.001f, 100.0f);
      shader->set<glm::mat4>("view", view);
      shader->set<glm::mat4>("projection", proj);

      glm::mat4 model = glm::translate(
          glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)), (float)glm::degrees(0.01f * glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f)),
          glm::vec3(-1.5f, 0.0f, 0.0f));
      shader->set<glm::mat4>("model", model);

      // draw cube
      assets.get<Model>("cube")->draw();

      CHECK_ERRORS
    });
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}