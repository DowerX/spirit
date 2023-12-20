#include <engine/objects/object.h>
#include <memory>

namespace Engine::Objects {
void Object::update(double time, double delta_time) {
  for (std::shared_ptr<Components::Component> comp : components) {
    comp->update(time, delta_time);
  }

  for (auto child : children) {
    child.second->update(time, delta_time);
  }
}

} // namespace Engine::Objects