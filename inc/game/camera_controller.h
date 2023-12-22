#pragma once

#include <engine/objects/object.h>
#include <memory>

class CameraController : public Engine::Objects::Components::Component {
 private:
  float speed;
  float sensitivity;

  std::shared_ptr<Engine::Objects::Components::Transform> transform;

 public:
  CameraController(Engine::Objects::Object& owner)
      : Engine::Objects::Components::Component(owner),
        speed(3.0f),
        sensitivity(100),
        transform(owner.get_component<Engine::Objects::Components::Transform>()) {}

  void set_speed(float speed) { this->speed = speed; }
  float get_speed() const { return speed; }

  void update(double, double delta_time) override;
};