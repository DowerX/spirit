#pragma once

#include <engine/types/vector.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <type_traits>

namespace Engine::Graphics {
class Shader {
 private:
  GLuint id;

  template <typename T>
  struct is_supported_type : std::false_type {};
  template <>
  struct is_supported_type<bool> : std::true_type {};
  template <>
  struct is_supported_type<int> : std::true_type {};
  template <>
  struct is_supported_type<float> : std::true_type {};
  template <>
  struct is_supported_type<Types::Vector<2, float>> : std::true_type {};
  template <>
  struct is_supported_type<Types::Vector<3, float>> : std::true_type {};
  template <>
  struct is_supported_type<Types::Vector<2, int>> : std::true_type {};
  template <>
  struct is_supported_type<Types::Vector<3, int>> : std::true_type {};
  template <>
  struct is_supported_type<glm::vec<3, float>> : std::true_type {};
  template <>
  struct is_supported_type<glm::mat4> : std::true_type {};

 public:
  Shader(const char* vert_src, const char* frag_src);
  ~Shader();

  static std::shared_ptr<Shader> from_file(const std::string& vert_path, const std::string& frag_path);

  template <typename T, typename = typename std::enable_if<is_supported_type<T>::value>::type>
  void set(const std::string& name, const T& value);

  void use();
};

} // namespace Engine::Graphics