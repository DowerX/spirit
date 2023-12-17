#include <engine/graphics/shader.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

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
  glGetShaderiv(id, GL_LINK_STATUS, &success);
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
  std::string vert_src = sstream.str();

  sstream.str("");

  std::ifstream frag_file(frag_path);
  if (!frag_file.is_open())
    throw std::runtime_error("failed to open fragment shader source: " + frag_path);

  sstream << frag_file.rdbuf();
  std::string frag_src = sstream.str();

  std::cout << vert_src << std::endl << frag_src << std::endl;

  return std::make_shared<Shader>(vert_src.c_str(), frag_src.c_str());
}

void Shader::use() {
  glUseProgram(id);
}
} // namespace Engine::Graphics