#include <game/rotator_component.h>

void Rotator::update(double, double delta_time) {
  // float size = (sin(time) + 1.0f) / 30 + 0.02f;
  // transform->set_local_scale(glm::vec3(size, size, size) * scale);
  transform->local_rotate(glm::vec3(0.0f, 100.0f, 0.0f) * (float)delta_time);
}