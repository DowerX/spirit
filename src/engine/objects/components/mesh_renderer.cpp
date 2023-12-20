#include <engine/objects/components/mesh_renderer.h>
#include <glm/fwd.hpp>

namespace Engine::Objects::Components {
void MeshRenderer::start() {
  transform = get_owner().get_component<Transform>();
}

void MeshRenderer::update(double,double delta_time) {
  (void)delta_time;
  material->use();
  material->get_shader()->set<glm::mat4>("model", transform->get_transform());
  mesh->draw();
}

} // namespace Engine::Objects::Components