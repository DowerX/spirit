#include <engine/assets/model.h>

namespace Engine::Assets {
void Model::draw() {
  material->use();
  mesh->draw();
}
} // namespace Engine::Assets::Objects