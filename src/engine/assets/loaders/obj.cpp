#include <engine/assets/loaders/obj.h>
#include <engine/assets/mesh.h>
#include <engine/types/vector.h>
#include <engine/utility.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef BUNDLE
#include <bundler/bundler.h>
#endif

using namespace Engine::Assets;
using namespace Engine::Utility;
using namespace Engine::Graphics;
using namespace Engine::Types;

namespace Engine::Assets::Loaders {
std::shared_ptr<Mesh> obj(const std::string& path) {
#ifndef BUNDLE
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("failed to open OBJ file: " + path);
#endif
#ifdef BUNDLE
  Bundler::Asset asset = Bundler::get_asset(path);
  std::string data((char*)asset.data, asset.len);
  std::stringstream file(data);
#endif

  std::vector<Vector<3, GLfloat>> vertices;
  std::vector<Vector<3, GLfloat>> normals;
  std::vector<Vector<2, GLfloat>> texture_coordinates;
  std::vector<GLuint> indices;

  size_t point_index = 0;
  std::map<std::string, std::tuple<size_t, size_t, size_t, size_t>> points;

  std::string line;
  while (std::getline(file, line, '\n')) {
    std::vector<std::string> parts = split(line, ' ');
    if (line.starts_with("v ")) {
      vertices.push_back(Vector<3, float>({std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3])}));
    } else if (line.starts_with("vn ")) {
      normals.push_back(Vector<3, float>({std::stof(parts[1]), std::stof(parts[2]), std::stof(parts[3])}));
    } else if (line.starts_with("vt ")) {
      texture_coordinates.push_back(Vector<2, float>({std::stof(parts[1]), std::stof(parts[2])}));
    } else if (line.starts_with("f ")) {
      for (int i = 1; i < 4; i++) {
        if (!points.contains(parts[i])) {
          std::vector<std::string> seg = split(parts[i], '/');
          points[parts[i]] = std::tuple(point_index++, std::stoul(seg[0]) - 1, std::stoul(seg[1]) - 1, std::stoul(seg[2]) - 1);
        }

        indices.push_back(std::get<0>(points[parts[i]]));
      }
    }
  }

  std::vector<GLfloat> buffer;
  std::vector<std::tuple<size_t, size_t, size_t, size_t>> sorted_points;
  for (const auto& point : points) {
    sorted_points.push_back(point.second);
  }

  std::sort(sorted_points.begin(), sorted_points.end(), [](const auto& a, const auto& b) { return std::get<0>(a) < std::get<0>(b); });

  for (const auto& point : sorted_points) {
    Vector<3, GLfloat> vertex = vertices[std::get<1>(point)];
    buffer.push_back(vertex.get(0));
    buffer.push_back(vertex.get(1));
    buffer.push_back(vertex.get(2));
    Vector<3, GLfloat> normal = normals[std::get<3>(point)];
    buffer.push_back(normal.get(0));
    buffer.push_back(normal.get(1));
    buffer.push_back(normal.get(2));
    Vector<2, GLfloat> texture = texture_coordinates[std::get<2>(point)];
    buffer.push_back(texture.get(0));
    buffer.push_back(texture.get(1));
  }

  return std::make_shared<Mesh>(
      buffer, indices,
      std::vector<VAO::Attribute>{
          {.index = 0, .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 8 * sizeof(float), .offset = (void*)0},
          {.index = 1, .size = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 8 * sizeof(float), .offset = (void*)(3 * sizeof(float))},
          {.index = 2, .size = 2, .type = GL_FLOAT, .normalized = GL_FALSE, .stride = 8 * sizeof(float), .offset = (void*)(6 * sizeof(float))}});
}
} // namespace Engine::Assets::Loaders
