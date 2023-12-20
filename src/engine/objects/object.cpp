#include <engine/objects/object.h>
#include <memory>

namespace Engine::Objects {
void Object::early_update(double time, double delta_time) {
  for (std::shared_ptr<Components::Component> comp : components) {
    comp->early_update(time, delta_time);
  }

  for (auto child : children) {
    child.second->early_update(time, delta_time);
  }
}

void Object::update(double time, double delta_time) {
  for (std::shared_ptr<Components::Component> comp : components) {
    comp->update(time, delta_time);
  }

  for (auto child : children) {
    child.second->update(time, delta_time);
  }
}

void Object::late_update(double time, double delta_time) {
  for (std::shared_ptr<Components::Component> comp : components) {
    comp->late_update(time, delta_time);
  }

  for (auto child : children) {
    child.second->late_update(time, delta_time);
  }
}

} // namespace Engine::Objects