#include <engine/utility.h>
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
} // namespace Engine::Utility