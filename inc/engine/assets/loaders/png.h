#pragma once

#include <engine/assets/texture.h>
#include <memory>
#include <string>

namespace Engine::Assets::Loaders {

std::shared_ptr<Engine::Assets::Texture> png(const std::string& path);

}