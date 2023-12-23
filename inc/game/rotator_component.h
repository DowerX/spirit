#include <engine/objects/object.h>
#include <memory>

class Rotator : public Engine::Objects::Components::Component {
 private:
  std::shared_ptr<Engine::Objects::Components::Transform> transform;
  float scale = 1.0f;

 public:
  Rotator() {}

  void set_scale(float scale) { this->scale = scale; }

  void start() override;
  void update(double time, double delta_time) override;
};