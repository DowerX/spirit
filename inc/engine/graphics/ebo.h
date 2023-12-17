#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <vector>

namespace Engine::Graphics {
// Element Buffer Object
class EBO {
 private:
  GLuint id;
  uint32_t size;

 public:
  EBO(const std::vector<GLuint>& indices);
  ~EBO();

  uint32_t get_size() const { return size; }

  void bind();
};
} // namespace Engine::Graphics