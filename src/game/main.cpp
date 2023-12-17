#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/assets/loaders.h>
#include <engine/assets/mesh.h>
#include <engine/graphics/shader.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Engine;
using namespace Engine::Graphics;
using namespace Engine::Assets;

const std::vector<GLfloat> vertices = {
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f // top left
};
const std::vector<GLuint> indices = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};

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

  Mesh mesh = Loaders::obj("assets/meshes/suzanne/suzanne.obj");
  // Mesh mesh = Loaders::obj("assets/meshes/cube/cube.obj");

  shader->use();

  app->run([&]() {
    glm::mat4 model =
        glm::rotate(glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f)), (float)glm::degrees(0.01f * glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f));
    glm::mat4 proj = glm::perspective(glm::radians(75.0f), 4.0f / 3, 0.1f, 100.0f);
    shader->set<glm::mat4>("model", model);
    shader->set<glm::mat4>("view", view);
    shader->set<glm::mat4>("projection", proj);
    mesh.draw();
  });

  return 0;
}