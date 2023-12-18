#include <engine/assets/mesh.h>
#include <string>

namespace Engine::Assets::Loaders {
std::shared_ptr<Mesh> obj(const std::string& path);
} // namespace Engine::Assets::Loaders