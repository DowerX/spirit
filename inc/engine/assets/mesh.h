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
  std::shared_ptr<Graphics::VBO> vbo;
  std::shared_ptr<Graphics::EBO> ebo;
  std::shared_ptr<Graphics::VAO> vao;

 public:
  Mesh(const std::vector<GLfloat> vertices, const std::vector<GLuint> indices, std::vector<Graphics::VAO::Attribute> attributes);
  ~Mesh() {}

  void draw() override;
};
} // namespace Engine::Assets