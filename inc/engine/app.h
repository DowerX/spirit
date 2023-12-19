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

  void process_input();

 public:
  struct Config {
    int sync_interval;
    std::string title;
    uint32_t width;
    uint32_t height;

    Config() {}
    Config(int sync, const std::string& title, uint32_t width, uint32_t height) : sync_interval(sync), title(title), width(width), height(height) {}
  };

  App(const Config& config);
  App(uint32_t width, uint32_t height) : App(Config(1, "Spirit", width, height)) {}
  App() : App(800, 600) {}
  ~App();

  uint32_t get_width() const { return width; }
  uint32_t get_height() const { return height; }
  float get_aspect_ratio() const { return (float)width / height; }

  Assets::Manager& get_asset_manager() { return asset_manager; }

  void run(const std::function<void()>& loop);
};

} // namespace Engine