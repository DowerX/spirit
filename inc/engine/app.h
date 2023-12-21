#pragma once

#include <GLFW/glfw3.h>
#include <engine/assets/manager.h>
#include <functional>
#include <string>

namespace Engine {
class App {
 private:
  GLFWwindow* window;
  uint32_t width;
  uint32_t height;
  double delta_time;

  Assets::Manager asset_manager;

  App();

 public:
  App(const App&) = delete;
  void operator=(const App&) = delete;

  static App& get_instance();

  ~App();

  struct Config {
    int sync_interval;
    std::string title;
    uint32_t width;
    uint32_t height;
    GLFWmonitor* monitor;

    Config(int sync, const std::string& title, uint32_t width, uint32_t height, GLFWmonitor* monitor)
        : sync_interval(sync), title(title), width(width), height(height), monitor(monitor) {}
    Config(uint32_t width, uint32_t height) : Config(1, "Spirit", width, height, nullptr) {}
    Config() : Config(800, 600) {}
  };

  static void initialize(const Config& config);

  GLFWwindow* get_window() const { return window; }
  uint32_t get_width() const { return width; }
  uint32_t get_height() const { return height; }
  float get_aspect_ratio() const { return (float)width / height; }

  float get_delta_time() const { return delta_time; }

  Assets::Manager& get_asset_manager() { return asset_manager; }

  void run();
};

} // namespace Engine