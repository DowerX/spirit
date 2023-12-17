#include <engine/graphics/vao.h>
#include <glad/glad.h>
#include <vector>

namespace Engine::Graphics {
VAO::VAO(const std::vector<Attribute>& attributes) {
  glGenVertexArrays(1, &id);
  glBindVertexArray(id);
  for (Attribute attribute : attributes) {
    attribute.vbo->bind();
    glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride, attribute.offset);
    glEnableVertexAttribArray(attribute.index);
  }
}

VAO::~VAO() {
  glDeleteVertexArrays(1, &id);
}

void VAO::bind() {
  glBindVertexArray(id);
}
} // namespace Engine::Graphics