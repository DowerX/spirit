#pragma once

#include <engine/assets/texture.h>
#include <memory>
#include <string>

namespace Engine::Assets::Loaders {
std::shared_ptr<Texture> png(const std::string& path);
}