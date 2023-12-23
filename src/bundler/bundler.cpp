#include <mapping.h>
#include <map>

namespace Bundler {

const Asset& get_asset(const std::string& path) {
  return assets.at(path);
}
} // namespace Bundler
