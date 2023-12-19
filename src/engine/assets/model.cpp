#include <engine/assets/model.h>
#include <glm/ext/matrix_transform.hpp>

const glm::vec3 left(1.0f, 0.0f, 0.0f);
const glm::vec3 up(0.0f, 1.0f, 0.0f);
const glm::vec3 forward(0.0f, 0.0f, 1.0f);
const glm::mat4 identity(1.0f);

namespace Engine::Assets {
Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : mesh(mesh), material(material), position(position), rotation(rotation), scale(scale) {
  set_transform_matrix();
}

void Model::set_transform_matrix() {
  transform_matrix = identity;
  transform_matrix = glm::translate(transform_matrix, position);
  transform_matrix = glm::scale(transform_matrix, scale);

  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.x), left);
  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.y), up);
  transform_matrix = glm::rotate(transform_matrix, glm::radians(rotation.z), forward);
}

void Model::set_position(const glm::vec3& position) {
  this->position = position;
  set_transform_matrix();
}
void Model::set_rotation(const glm::vec3& rotation) {
  this->rotation = rotation;
  set_transform_matrix();
}
void Model::set_scale(const glm::vec3& scale) {
  this->scale = scale;
  set_transform_matrix();
}

void Model::translate(const glm::vec3& translation) {
  position += translation;
  set_transform_matrix();
}
void Model::rotate(const glm::vec3& rotation) {
  this->rotation += rotation;
  set_transform_matrix();
}

void Model::draw() {
  material->use();
  material->get_shader()->set<glm::mat4>("model", transform_matrix);
  mesh->draw();
}
} // namespace Engine::Assets