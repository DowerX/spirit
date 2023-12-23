#pragma once

#include <string>

#define ASSET(path, name)             \
  {                                   \
    path, {                           \
      .data = name, .len = name##_len \
    }                                 \
  }

namespace Bundler {
struct Asset {
  unsigned char* data;
  unsigned int len;
};

const Asset& get_asset(const std::string& path);
} // namespace Bundler