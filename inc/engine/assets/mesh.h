#pragma once

#include <engine/assets/drawable.h>
#include <engine/graphics/ebo.h>
#include <engine/graphics/vao.h>
#include <engine/graphics/vbo.h>
#include <memory>
#include <vector>

namespace Engine::Assets {
class Mesh : public Drawable {
 private:
  std::unique_ptr<Graphics::VBO> vbo;
  std::unique_ptr<Graphics::EBO> ebo;
  std::unique_ptr<Graphics::VAO> vao;

 public:
  Mesh(const std::vector<GLfloat> vertices, const std::vector<GLuint> indices, std::vector<Graphics::VAO::Attribute> attributes);
  ~Mesh() {}

  void draw() override;
};
} // namespace Engine::Assets