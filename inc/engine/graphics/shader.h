#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>

namespace Engine::Graphics {
class Shader {
 private:
  GLuint id;

 public:
  Shader(const char* vert_src, const char* frag_src);
  ~Shader();

  static std::shared_ptr<Shader> from_file(const std::string& vert_path, const std::string& frag_path);

  void use();
};

} // namespace Engine::Graphics