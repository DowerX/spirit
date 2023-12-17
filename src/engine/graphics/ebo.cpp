#include <engine/graphics/ebo.h>
#include <glad/glad.h>
#include <vector>

namespace Engine::Graphics {
EBO::EBO(const std::vector<GLuint>& indices) : size(indices.size()) {
  glGenBuffers(1, &id);
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

EBO::~EBO() {
  glDeleteBuffers(1, &id);
}

void EBO::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}
} // namespace Engine::Graphics