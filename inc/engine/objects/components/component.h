#pragma once

namespace Engine::Objects {
class Object;
}

namespace Engine::Objects::Components {
class Component {
 private:
  Engine::Objects::Object* owner;

 public:
  Component() {}
  virtual ~Component() = default;

  void set_owner(Object* owner);
  Object& get_owner() const { return *owner; }

  // called once
  virtual void start(){};

  // called every frame
  virtual void early_update(double, double){};
  virtual void update(double, double){};
  virtual void late_update(double, double){};
};

} // namespace Engine::Objects::Components