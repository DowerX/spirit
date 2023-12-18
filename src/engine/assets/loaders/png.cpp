#include <engine/assets/loaders/png.h>
#include <glad/glad.h>
#include <memory>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace Engine::Assets;

namespace Engine::Assets::Loaders {

std::shared_ptr<Texture> png(const std::string& path) {
  int width, height, channels;

  stbi_set_flip_vertically_on_load(true);

  uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (data == nullptr)
    throw std::runtime_error("failed to load PNG texture: " + path);

  GLenum format;
  switch (channels) {
    case 1:
      format = GL_RED;
      break;
    case 2:
      format = GL_RG;
      break;
    case 3:
      format = GL_RGB;
      break;
    case 4:
      format = GL_RGBA;
      break;
  }

  std::shared_ptr<Texture> texture = std::make_shared<Texture>(GL_TEXTURE_2D, GL_RGBA, width, height, format, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

  return texture;
}

} // namespace Engine::Assets::Loaders