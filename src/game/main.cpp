#include <engine/app.h>
#include <engine/assets/loaders.h>
#include <engine/assets/mesh.h>
#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "engine/utility.h"

using namespace Engine;
using namespace Engine::Graphics;
using namespace Engine::Assets;
using namespace Engine::Utility;

int main() {
  std::unique_ptr<App> app;
  try {
    app = std::make_unique<App>(800, 600);
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  std::shared_ptr<Shader> shader;
  try {
    shader = Shader::from_file("assets/shaders/basic/basic.vert", "assets/shaders/basic/basic.frag");
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  std::shared_ptr<Mesh> mesh;
  try {
    mesh = Loaders::obj("assets/meshes/cube/cube.obj");
    // mesh = Loaders::obj("assets/meshes/suzanne/suzanne.obj");
    // mesh = Loaders::obj("assets/meshes/teapot/teapot.obj");
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  std::shared_ptr<Texture> texture;
  try {
    texture = Loaders::png("assets/textures/cube.png");
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  app->run([&]() {
    shader->use();
    texture->bind(0);
    shader->set<int>("texture0", 0);
    glm::mat4 model =
        glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)), (float)glm::degrees(0.01f * glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f));
    glm::mat4 proj = glm::perspective(glm::radians(75.0f), app->get_aspect_ratio(), 0.1f, 100.0f);

    shader->set<glm::mat4>("view", view);
    shader->set<glm::mat4>("projection", proj);
    shader->set<glm::mat4>("model", model);

    mesh->draw();
  });

  return 0;
}