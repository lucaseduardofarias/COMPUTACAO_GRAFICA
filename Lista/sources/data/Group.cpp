#include "../../headers/data/Group.h"

Group::Group() {}

Group::~Group() {
    this->faces.clear();
    this->faces.shrink_to_fit();

    glDeleteVertexArrays(1, &vao);
    for (auto& vbo : this->vbos) {
        glDeleteBuffers(1, &vbo);
    }

    this->vbos.clear();
    this->vbos.shrink_to_fit();
}

Face* Group::face(int id) {
    return this->faces[id];
}

int Group::addFace(Face* face) {
    this->faces.push_back(face);
    return this->faces.size() - 1;
}
