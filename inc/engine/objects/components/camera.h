#pragma once

#include <engine/assets/manager.h>
#include <engine/objects/object.h>
#include <memory>

namespace Engine::Objects::Components {
class Camera : public Component {
 private:
  float fov;
  float near;
  float far;
  float aspect_ratio;

  glm::mat4 projection;

  std::shared_ptr<Transform> transform;

  Assets::Manager* manager;

  void set_projection();

 public:
  Camera(Object& owner) : Component(owner), fov(75.0f), near(0.001f), far(1000.0f), aspect_ratio(4.0f / 3), transform(owner.get_component<Transform>()) {
    set_projection();
  }

  void set_fov(float fov);
  void set_near(float near);
  void set_far(float far);
  void set_aspect_ratio(float aspect_ratio);

  void set_asset_manager(Assets::Manager* manager) { this->manager = manager; }

  float get_fov() const { return fov; }
  float get_near() const { return near; }
  float get_far() const { return far; }
  float get_aspect_ratio() const { return aspect_ratio; }

  void early_update(double, double) override;
};
} // namespace Engine::Objects::Components