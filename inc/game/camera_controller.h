#pragma once

#include <engine/objects/object.h>
#include <memory>

class CameraController : public Engine::Objects::Components::Component {
 private:
  float speed;
  float sensitivity;

  std::shared_ptr<Engine::Objects::Components::Transform> transform;

 public:
  CameraController() : speed(3.0f), sensitivity(100), transform() {}

  void set_speed(float speed) { this->speed = speed; }
  float get_speed() const { return speed; }

  void start() override;
  void update(double, double delta_time) override;
};