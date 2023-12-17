#pragma once

#include <glad/glad.h>
#include <vector>

namespace Engine::Graphics {
// Element Buffer Object
class EBO {
 private:
  GLuint id;

 public:
  EBO(const std::vector<GLuint>& indices);
  ~EBO();

  void bind();
};
} // namespace Engine::Graphics