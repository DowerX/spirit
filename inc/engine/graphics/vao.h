#pragma once

#include <engine/graphics/vbo.h>
#include <glad/glad.h>
#include <memory>
#include <vector>

namespace Engine::Graphics {
// Vertex Array Object
class VAO {
 private:
  GLuint id;

 public:
  struct Attribute {
    std::shared_ptr<VBO> vbo;
    GLuint index;
    GLuint size;
    GLuint type;
    GLboolean normalized;
    GLuint stride;
    void* offset;
  };

  VAO(const std::vector<Attribute>& attributes);
  ~VAO();

  void bind();
};
} // namespace Engine::Graphics