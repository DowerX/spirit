#include <engine/app.h>
#include <engine/graphics/ebo.h>
#include <engine/graphics/shader.h>
#include <engine/graphics/vao.h>
#include <engine/graphics/vbo.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Engine;
using namespace Engine::Graphics;

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

  std::shared_ptr<VBO> vbo = std::make_shared<VBO>(vertices);
  std::shared_ptr<EBO> ebo = std::make_shared<EBO>(indices);
  std::shared_ptr<VAO> vao = std::make_shared<VAO>(std::vector<VAO::Attribute>{
      {.vbo = vbo, .index = 0, .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 3 * sizeof(float), .offset = (void*)0}});

  vao->bind();
  vbo->bind();
  ebo->bind();
  shader->use();

  app->run();

  return 0;
}