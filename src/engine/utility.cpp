#include <engine/utility.h>
#include <glad/glad.h>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Engine::Utility {
std::vector<std::string> split(const std::string& input, char delimiter) {
  std::vector<std::string> parts;
  std::istringstream stream(input);
  std::string part;
  while (std::getline(stream, part, delimiter))
    parts.push_back(part);
  return parts;
}

bool get_opengl_errors() {
#ifdef DEBUG
  GLenum error;
  bool found = false;
  while ((error = glGetError()) != GL_NO_ERROR) {
    std::string error_text;
    switch (error) {
      case GL_INVALID_ENUM:
        error_text = "invalid enum";
        break;
      case GL_INVALID_VALUE:
        error_text = "invalid value";
        break;
      case GL_INVALID_OPERATION:
        error_text = "invalid operation";
        break;
      case GL_OUT_OF_MEMORY:
        error_text = "out of memory";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        error_text = "invalid framebuffer operation";
        break;
      default:
        error_text = "unknown error: " + std::to_string(error);
    }
    std::cerr << error_text << std::endl;
    found = true;
  }
  return found;
#endif
  return false;
}

bool get_opengl_errors(size_t line) {
#ifdef DEBUG
  if (get_opengl_errors()) {
    std::cerr << "line: " << std::to_string(line) << std::endl;
    return true;
  }
  return false;
#endif
  (void)line;
  return false;
}
} // namespace Engine::Utility