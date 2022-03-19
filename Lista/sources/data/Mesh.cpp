#include "../../headers/data/Mesh.h"

Mesh::Mesh() {}

Mesh::~Mesh() {
    this->groups.clear();
    this->groups.shrink_to_fit();

    this->normais.clear();
    this->normais.shrink_to_fit();

    this->vertices.clear();
    this->vertices.shrink_to_fit();

    this->normais.clear();
    this->normais.shrink_to_fit();
}

glm::vec3* Mesh::vertice(int id) {
    return this->vertices[id];
}

glm::vec3* Mesh::normal(int id) {
    return this->normais[id];
}

glm::vec2* Mesh::texture(int id) {
    return this->textures[id];
}

void Mesh::setName(string name) {
    this->name = name;
}

void Mesh::setMaterial(string material) {
    this->material = material;
}

int Mesh::addGroup(Group* group) {
    this->groups.push_back(group);
    return this->groups.size() - 1;
}

int Mesh::addVertice(glm::vec3* vertice) {
    this->vertices.push_back(vertice);
    return this->vertices.size() - 1;
}

int Mesh::addNormal(glm::vec3* normal) {
    this->normais.push_back(normal);
    return this->normais.size() - 1;
}

int Mesh::addTexture(glm::vec2* texture) {
    this->textures.push_back(texture);
    return this->textures.size() - 1;
}

void Mesh::setShader(Shader* shader) {
    this->shader = shader;
}

void Mesh::setShaderColor(Shader* shaderColor) {
    this->shaderColor = shaderColor;
}
