cmake_minimum_required(VERSION 3.25)

project("spirit" VERSION 1.0)

# compiler setup
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") # warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")            # std c++23
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_NONE")   # disable gfwl opengl

if(DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")                  # debug symbols
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")                   # optimisations

# IDE setup (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

# engine
file(GLOB_RECURSE ENGINE_SOURCES "${CMAKE_SOURCE_DIR}/src/engine/*.cpp" "${CMAKE_SOURCE_DIR}/src/glad/glad.c")
add_library("engine" SHARED ${ENGINE_SOURCES})
set_target_properties("engine" PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories("engine" PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries("engine" glfw glm)

# game
file(GLOB_RECURSE GAME_SOURCES "${CMAKE_SOURCE_DIR}/src/game/*.cpp")
add_executable("game.bin" ${GAME_SOURCES})
target_include_directories("game.bin" PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries("game.bin" "engine" glm)