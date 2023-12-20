#include <engine/objects/components/mesh_renderer.h>
#include <glm/fwd.hpp>

namespace Engine::Objects::Components {
void MeshRenderer::late_update(double,double) {
  material->use();
  material->get_shader()->set<glm::mat4>("model", transform->get_transform());
  mesh->draw();
}

} // namespace Engine::Objects::Components