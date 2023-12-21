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

  float shininess;
  float specular_strenght;

 public:
  Material(const std::shared_ptr<Graphics::Shader> shader, const std::vector<TextureSlot>& textures)
      : shader(shader), textures(textures), shininess(32), specular_strenght(0.5) {}

  std::shared_ptr<Graphics::Shader> get_shader() const { return shader; }
  std::vector<TextureSlot>& get_textures() { return textures; }

  void set_shininess(float value) { this->shininess = value; }
  void set_specular_strenght(float value) { this->specular_strenght = value; }

  float get_shininess() const { return shininess; }
  float get_specular_strenght() const { return specular_strenght; }

  void use() const;
};

} // namespace Engine::Assets