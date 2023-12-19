#include <engine/assets/mesh.h>
#include <memory>

using namespace Engine::Graphics;

namespace Engine::Assets {
Mesh::Mesh(const std::vector<GLfloat> vertices, const std::vector<GLuint> indices, std::vector<Graphics::VAO::Attribute> attributes)
    : vbo(std::make_unique<VBO>(vertices)), ebo(std::make_unique<EBO>(indices)) {
  for (VAO::Attribute& attr : attributes) {
    attr.vbo = vbo->get_id();
  }

  vao = std::make_unique<VAO>(attributes);
}

void Mesh::draw() {
  vao->bind();
  ebo->bind();
  glDrawElements(GL_TRIANGLES, ebo->get_size(), GL_UNSIGNED_INT, 0);
}

} // namespace Engine::Assets