#include <engine/objects/components/mesh_renderer.h>
#include <glm/fwd.hpp>

namespace Engine::Objects::Components {
void MeshRenderer::late_update(double, double) {
  material->use();
  material->get_shader()->set<glm::mat4>("model", transform->get_transform());
  material->get_shader()->set<float>("shininess", material->get_shininess());
  material->get_shader()->set<float>("specular_strenght", material->get_specular_strenght());
  mesh->draw();
}

} // namespace Engine::Objects::Components