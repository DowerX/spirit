#include <engine/graphics/vbo.h>
#include <glad/glad.h>
#include <vector>

namespace Engine::Graphics {
VBO::VBO(const std::vector<GLfloat>& vertices) {
  glGenBuffers(1, &id);
  bind();
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO() {
  glDeleteBuffers(1, &id);
}

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}
} // namespace Engine::Graphics