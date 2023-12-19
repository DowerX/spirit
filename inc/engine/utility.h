#pragma once

#include <cstddef>
#include <string>
#include <vector>
namespace Engine::Utility {
std::vector<std::string> split(const std::string& input, char delimiter);

bool get_opengl_errors();
bool get_opengl_errors(size_t line);

#ifdef DEBUG
#define CHECK_ERRORS Engine::Utility::get_opengl_errors(__LINE__);
#endif
#ifndef DEBUG
#define CHECK_ERRORS
#endif

} // namespace Engine::Utility