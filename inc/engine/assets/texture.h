#pragma once

#include <glad/glad.h>

namespace Engine::Assets {
class Texture {
 private:
  GLuint id;
  GLenum target;

 public:
  Texture(GLenum target, GLint internal_format, GLsizei width, GLsizei height, GLint format, GLenum type, const void* data);
  ~Texture();

  void bind(uint8_t slot) const;
};

} // namespace Engine::Assets