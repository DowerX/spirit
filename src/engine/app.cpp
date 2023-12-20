#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/utility.h>
#include <glad/glad.h>
#include <cstdint>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>

namespace Engine {

std::map<GLFWwindow*, std::function<void(int, int)>> windowCallbacks;

void resize_callback(GLFWwindow* window, int width, int height) {
  windowCallbacks[window](width, height);
}

App::App(const Config& config) : width(config.width), height(config.height) {
  if (glfwInit() != GL_TRUE)
    throw std::runtime_error("failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, config.title.c_str(), config.monitor, nullptr);
  if (window == nullptr)
    throw std::runtime_error("failed to create a window");

  glfwMakeContextCurrent(window);

  // glfwSwapInterval(config.sync_interval);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("failed to initialize GLAD");

  windowCallbacks[window] = [&](int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
  };
  glfwSetFramebufferSizeCallback(window, resize_callback);

  glClearColor(0.2, 0.3, 0.3, 1);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
}

App::~App() {
  glfwTerminate();
}

void App::run(const std::function<void()>& loop) {
  double last_time = 0;

#ifdef DEBUG
  double last = 0;
  uint32_t frame_count = 0;
#endif

  while (!glfwWindowShouldClose(window)) {
    double time = glfwGetTime();
#ifdef DEBUG
    frame_count++;
    if (time - last >= 1) {
      glfwSetWindowTitle(window, std::to_string(frame_count / (time - last)).c_str());
      last = time;
      frame_count = 0;
    }
#endif

    delta_time = time - last_time;
    last_time = time;

    glfwPollEvents();
    process_input();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    loop();

    asset_manager.get_root_object()->early_update(time, delta_time);
    asset_manager.get_root_object()->update(time, delta_time);
    asset_manager.get_root_object()->late_update(time, delta_time);

    CHECK_ERRORS

    glfwSwapBuffers(window);
  }
}

void App::process_input() {}

} // namespace Engine