#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include <engine/objects/components/component.h>
#include <engine/objects/components/transform.h>

namespace Engine::Objects {

class Object {
 private:
  Object* parent;
  std::map<std::string, std::shared_ptr<Object>> children;

  std::vector<std::shared_ptr<Components::Component>> components;

 public:
  Object() { add_component<Components::Transform>(); }
  Object(Object* parent) : parent(parent) { add_component<Components::Transform>(); }

  Object* get_parent() { return parent; }

  std::shared_ptr<Object> add_child(const std::string& name) {
    children[name] = std::make_shared<Object>(this);
    return children[name];
  }
  std::map<std::string, std::shared_ptr<Object>>& get_children() { return children; }
  std::shared_ptr<Object> get_child(const std::string& name) { return children[name]; }

  template <typename T>
  std::shared_ptr<T> add_component() {
    std::shared_ptr<T> comp = std::make_shared<T>(*this);
    components.push_back(comp);
    comp->start();
    return comp;
  }
  std::vector<std::shared_ptr<Components::Component>>& get_components() { return components; }

  template <typename T>
  std::shared_ptr<T> get_component() {
    std::shared_ptr<T> result;
    for (std::shared_ptr<Components::Component> comp : components) {
      if ((result = std::dynamic_pointer_cast<T>(comp)) != nullptr)
        return result;
    }
    return result;
  }

  void early_update(double time, double delta_time);
  void update(double time, double delta_time);
  void late_update(double time, double delta_time);
};

} // namespace Engine::Objects
