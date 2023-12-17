#include <engine/assets/mesh.h>
#include <memory>

using namespace Engine::Graphics;

namespace Engine::Assets {
Mesh::Mesh(const std::vector<GLfloat> vertices, const std::vector<GLuint> indices, std::vector<Graphics::VAO::Attribute> attributes)
    : vbo(std::make_shared<VBO>(vertices)), ebo(std::make_shared<EBO>(indices)) {
  for (VAO::Attribute& attr : attributes) {
    attr.vbo = vbo;
  }

  vao = std::make_shared<VAO>(attributes);
}

void Mesh::draw() {
  vbo->bind();
  ebo->bind();
  vao->bind();
  glDrawElements(GL_TRIANGLES, ebo->get_size(), GL_UNSIGNED_INT, 0);
}

} // namespace Engine::Assets