#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <functional>
#include <string>
#include "engine/assets/manager.h"

namespace Engine {
class App {
 private:
  GLFWwindow* window;
  uint32_t width;
  uint32_t height;

  Assets::Manager asset_manager;

  float delta_time;

  void process_input();

 public:
  struct Config {
    int sync_interval;
    std::string title;
    uint32_t width;
    uint32_t height;
    GLFWmonitor* monitor;

    Config() {}
    Config(int sync, const std::string& title, uint32_t width, uint32_t height, GLFWmonitor* monitor) : sync_interval(sync), title(title), width(width), height(height), monitor(monitor) {}
  };

  App(const Config& config);
  App(uint32_t width, uint32_t height) : App(Config(1, "Spirit", width, height, nullptr)) {}
  App() : App(800, 600) {}
  ~App();

  uint32_t get_width() const { return width; }
  uint32_t get_height() const { return height; }
  float get_aspect_ratio() const { return (float)width / height; }

  float get_delta_time() const { return delta_time; }

  Assets::Manager& get_asset_manager() { return asset_manager; }

  void run(const std::function<void()>& loop);
};

} // namespace Engine