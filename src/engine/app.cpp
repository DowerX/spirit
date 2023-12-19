#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <glad/glad.h>
#include <functional>
#include <map>
#include <stdexcept>

namespace Engine {

std::map<GLFWwindow*, std::function<void(int, int)>> windowCallbacks;

void resize_callback(GLFWwindow* window, int width, int height) {
  windowCallbacks[window](width, height);
}

App::App(const Config& config) : width(config.width), height(config.height){
  if (glfwInit() != GL_TRUE)
    throw std::runtime_error("failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, config.title.c_str(), nullptr, nullptr);
  if (window == nullptr)
    throw std::runtime_error("failed to create a window");

  glfwMakeContextCurrent(window);

  glfwSwapInterval(config.sync_interval);

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
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    process_input();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    loop();

    glfwSwapBuffers(window);
  }
}

void App::process_input() {}

} // namespace Engine