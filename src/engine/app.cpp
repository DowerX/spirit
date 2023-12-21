#include <GLFW/glfw3.h>
#include <engine/app.h>
#include <engine/input/mouse.h>
#include <engine/objects/components/camera.h>
#include <engine/objects/object.h>
#include <engine/utility.h>
#include <glad/glad.h>
#include <cstdint>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>

using namespace Engine::Input;

namespace Engine {

std::function<void(int, int)> window_resize_callbacks;

void resize_callback(GLFWwindow*, int width, int height) {
  window_resize_callbacks(width, height);
}
void mouse_callback(GLFWwindow*, double x, double y) {
  Mouse::mouse_callback(x, y);
}

App::App() {
  if (glfwInit() != GL_TRUE)
    throw std::runtime_error("failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

App& App::get_instance() {
  static App instance;
  return instance;
}

App::~App() {
  glfwTerminate();
}
void App::initialize(const Config& config) {
  App& app = get_instance();
  app.width = config.width;
  app.height = config.height;

  app.window = glfwCreateWindow(app.width, app.height, config.title.c_str(), config.monitor, nullptr);
  if (app.window == nullptr)
    throw std::runtime_error("failed to create a window");

  glfwMakeContextCurrent(app.window);

  glfwSwapInterval(0);
  // glfwSwapInterval(config.sync_interval);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("failed to initialize GLAD");

  glfwSetCursorPosCallback(app.window, mouse_callback);
  glfwSetInputMode(app.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  window_resize_callbacks = [&](int width, int height) {
    glViewport(0, 0, width, height);
    app.width = width;
    app.height = height;

    float aspect_ratio = (float)width / height;
    std::function<void(Objects::Object&)> update_aspect = [aspect_ratio, &update_aspect](Objects::Object& obj) {
      auto camera = obj.get_component<Objects::Components::Camera>();
      if (camera)
        camera->set_aspect_ratio(aspect_ratio);
      for (auto& child : obj.get_children()) {
        update_aspect(*child.second);
      }
    };

    update_aspect(*app.get_asset_manager().get_root_object());
  };
  glfwSetFramebufferSizeCallback(app.window, resize_callback);

  glClearColor(0.2, 0.3, 0.3, 1);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
}

void App::run() {
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

    Mouse::mouse_relative_reset();
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    asset_manager.get_root_object()->early_update(time, delta_time);
    asset_manager.get_root_object()->update(time, delta_time);
    asset_manager.get_root_object()->late_update(time, delta_time);

    glfwSwapBuffers(window);

    CHECK_ERRORS
  }
}
} // namespace Engine