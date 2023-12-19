#pragma once

#include <engine/assets/texture.h>
#include <engine/graphics/shader.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace Engine::Assets {
typedef std::pair<uint8_t, std::shared_ptr<Texture>> TextureSlot;

class Material {
 private:
  std::shared_ptr<Graphics::Shader> shader;
  std::vector<TextureSlot> textures;

 public:
  Material(const std::shared_ptr<Graphics::Shader> shader, const std::vector<TextureSlot>& textures) : shader(shader), textures(textures) {}

  std::shared_ptr<Graphics::Shader> get_shader() const { return shader; }

  void use() const;
};

} // namespace Engine::Assets