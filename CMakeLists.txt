cmake_minimum_required(VERSION 3.22)

project("spirit" VERSION 1.0)

# compiler setup
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") # warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")            # std c++23
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_NONE")   # disable gfwl opengl

if(DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")          # debug symbols
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")                   # optimisations

# IDE setup (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

# bundle assets
if (BUNDLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUNDLE")
  file(GLOB_RECURSE BUNDLER_OBJECTS "${CMAKE_SOURCE_DIR}/build/bundler/*.o")
  file(GLOB_RECURSE BUNDLER_SOURCES "${CMAKE_SOURCE_DIR}/src/bundler/*.cpp")
  
  add_library(assets SHARED ${BUNDLER_SOURCES})
  target_include_directories(assets PRIVATE "${CMAKE_SOURCE_DIR}/inc/bundler" "${CMAKE_SOURCE_DIR}/build/bundler")
  
  target_link_libraries(assets ${BUNDLER_OBJECTS})
endif()

# glad
add_library(glad SHARED "${CMAKE_SOURCE_DIR}/src/glad/glad.c")
target_include_directories(glad PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries(glad PRIVATE OpenGL::OpenGL)

# engine
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/*.cpp")
add_library(engine SHARED ${ENGINE_SOURCES})
set_target_properties(engine PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(engine PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries(engine PRIVATE glfw glm::glm glad OpenGL::OpenGL)

if (BUNDLE)
  target_link_directories(engine PRIVATE "${CMAKE_SOURCE_DIR}/build")
  target_link_libraries(engine PRIVATE "libassets.so")
endif()

# game
file(GLOB_RECURSE GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/game/*.cpp")
add_executable(game.bin ${GAME_SOURCES})
target_include_directories(game.bin PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries(game.bin PRIVATE engine)