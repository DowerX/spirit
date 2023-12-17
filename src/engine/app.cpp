#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <glad/glad.h>
#include <functional>
#include <stdexcept>
#include "engine/assets/mesh.h"

namespace Engine {
void resize_callback(GLFWwindow*, int width, int height) {
  glViewport(0, 0, width, height);
}

App::App(uint32_t width, uint32_t height) {
  if (glfwInit() != GL_TRUE)
    throw std::runtime_error("failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "opengl-test", nullptr, nullptr);
  if (window == nullptr)
    throw std::runtime_error("failed to create a window");

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("failed to initialize GLAD");

  glfwSetFramebufferSizeCallback(window, resize_callback);

  glClearColor(0.2, 0.3, 0.3, 1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
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