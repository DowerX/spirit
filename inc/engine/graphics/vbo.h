#pragma once

#include <glad/glad.h>
#include <vector>

namespace Engine::Graphics {
// Vertex Buffer Object
class VBO {
 private:
  GLuint id;

 public:
  VBO(const std::vector<GLfloat>& vertices);
  ~VBO();

  GLuint get_id() const { return id; }

  void bind();
};
} // namespace Engine::Graphics