#include <engine/assets/texture.h>
#include <iostream>

namespace Engine::Assets {

Texture::Texture(GLenum target, GLint internal_format, GLsizei width, GLsizei height, GLint format, GLenum type, const void* data) : target(target) {
  glGenTextures(1, &id);
  bind(0);

  glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(target, 0, internal_format, width, height, 0, format, type, data);
  glGenerateMipmap(target);
}

Texture::~Texture() {
  glDeleteTextures(1, &id);
}

void Texture::bind(uint8_t slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(target, id);
}
} // namespace Engine::Assets