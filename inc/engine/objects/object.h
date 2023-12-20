#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace Engine::Objects {

class Object;

namespace Components {
class Component {
 private:
  Engine::Objects::Object& owner;

 public:
  Component(Object& owner) : owner(owner) {}
  virtual ~Component() = default;

  Object& get_owner() { return owner; }

  // called once
  virtual void start(){};

  // called every frame
  virtual void early_update(double, double){};
  virtual void update(double, double){};
  virtual void late_update(double, double){};
};

class Transform : public Component {
 private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::mat4 transform_matrix;

 public:
  Transform(Object& owner, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3 scale)
      : Component(owner), position(position), rotation(rotation), scale(scale) {
    set_transform_matrix();
  }
  Transform(Object& owner) : Transform(owner, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)) {}

  void set_transform_matrix();

  void set_position(const glm::vec3& position);
  void set_rotation(const glm::vec3& rotation);
  void set_scale(const glm::vec3& scale);

  void translate(const glm::vec3& translation);

  void rotate(const glm::vec3& rotation);

  glm::vec3 get_position() const { return position; }
  glm::vec3 get_rotation() const { return rotation; }
  glm::vec3 get_scale() const { return scale; }
  glm::mat4 get_transform() const { return transform_matrix; }
};
} // namespace Components

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
    throw std::runtime_error("no matching component");
  }

  void early_update(double time, double delta_time);
  void update(double time, double delta_time);
  void late_update(double time, double delta_time);
};

} // namespace Engine::Objects
