#include <engine/graphics/shader.h>
#include <engine/types/vector.h>
#include <engine/utility.h>
#include <fstream>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace Engine::Types;
using namespace Engine::Utility;

namespace Engine::Graphics {

void shader_check(GLuint shader) {
  int success = 1;
  char info[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, info);
    throw std::runtime_error(info);
  }
}

Shader::Shader(const char* vert_src, const char* frag_src) {
  GLuint vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vert_src, nullptr);
  glCompileShader(vert);
  shader_check(vert);

  GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag, 1, &frag_src, nullptr);
  glCompileShader(frag);
  shader_check(frag);

  id = glCreateProgram();
  glAttachShader(id, vert);
  glAttachShader(id, frag);
  glLinkProgram(id);

  int success = 1;
  char info[512];
  get_opengl_errors(__LINE__);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  get_opengl_errors(__LINE__);
  if (!success) {
    glGetShaderInfoLog(id, 512, nullptr, info);
    throw std::runtime_error(info);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
}

Shader::~Shader() {
  glDeleteProgram(id);
}

std::shared_ptr<Shader> Shader::from_file(const std::string& vert_path, const std::string& frag_path) {
  std::stringstream sstream;

  std::ifstream vert_file(vert_path);
  if (!vert_file.is_open())
    throw std::runtime_error("failed to open vertex shader source: " + vert_path);

  sstream << vert_file.rdbuf();
  vert_file.close();
  std::string vert_src = sstream.str();

  sstream.str("");

  std::ifstream frag_file(frag_path);
  if (!frag_file.is_open())
    throw std::runtime_error("failed to open fragment shader source: " + frag_path);

  sstream << frag_file.rdbuf();
  frag_file.close();
  std::string frag_src = sstream.str();

  return std::make_shared<Shader>(vert_src.c_str(), frag_src.c_str());
}

template <>
void Shader::set<bool>(const std::string& name, const bool& value) {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
template <>
void Shader::set<int>(const std::string& name, const int& value) {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
template <>
void Shader::set<float>(const std::string& name, const float& value) {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

template <>
void Shader::set<Vector<2, float>>(const std::string& name, const Vector<2, float>& value) {
  glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, value.get());
}
template <>
void Shader::set<Vector<3, float>>(const std::string& name, const Vector<3, float>& value) {
  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value.get());
}

template <>
void Shader::set<Vector<2, int>>(const std::string& name, const Vector<2, int>& value) {
  glUniform2iv(glGetUniformLocation(id, name.c_str()), 1, value.get());
}
template <>
void Shader::set<Vector<3, int>>(const std::string& name, const Vector<3, int>& value) {
  glUniform3iv(glGetUniformLocation(id, name.c_str()), 1, value.get());
}

template <>
void Shader::set<glm::mat4>(const std::string& name, const glm::mat4& value) {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::use() {
  glUseProgram(id);
}
} // namespace Engine::Graphics