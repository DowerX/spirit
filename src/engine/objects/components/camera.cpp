#include <engine/graphics/shader.h>
#include <engine/objects/components/camera.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine::Graphics;

namespace Engine::Objects::Components {

void Camera::set_projection() {
  projection = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

void Camera::set_fov(float fov) {
  this->fov = fov;
  set_projection();
}
void Camera::set_near(float near) {
  this->near = near;
  set_projection();
}
void Camera::set_far(float far) {
  this->far = far;
  set_projection();
}
void Camera::set_aspect_ratio(float aspect_ratio) {
  this->aspect_ratio = aspect_ratio;
  set_projection();
}

void Camera::early_update(double, double) {
  for (auto& shader : manager.get_all<Shader>()) {
    shader.second->use();
    shader.second->set<glm::mat4>("view", transform->get_transform());
    shader.second->set<glm::mat4>("projection", projection);
  }
}

} // namespace Engine::Objects::Components