#include <engine/assets/material.h>

namespace Engine::Assets {

void Material::use() const {
  shader->use();
  for (const auto& texture : textures) {
    texture.second->bind(texture.first);
  }
}
} // namespace Engine::Assets