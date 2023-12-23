#include <engine/objects/components/component.h>
#include <engine/objects/object.h>

namespace Engine::Objects::Components {
void Component::set_owner(Object* owner) {
  this->owner = owner;
}

} // namespace Engine::Objects::Components