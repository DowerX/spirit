cmake_minimum_required(VERSION 3.25)

project("opengl-test" VERSION 1.0)

# compiler setup
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") # warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")            # std c++23
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_NONE")   # disable gfwl opengl

if (STATIC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")             # static
endif()

if (DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")                  # debug symbols
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")                   # optimisations

# IDE setup (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/glad/glad.c")
add_executable("opengl-test.bin" ${SOURCES})

target_include_directories("opengl-test.bin" PRIVATE "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries("opengl-test.bin" glfw glm)