#include <game/rotator_component.h>

void Rotator::update(double time, double delta_time) {
  float size = (sin(time) + 1.0f) / 30 + 0.02f;
  transform->set_scale(glm::vec3(size, size, size) * scale);
  transform->rotate(glm::vec3(10.0f, 10.0f, 10.0f) * (float)delta_time);
}