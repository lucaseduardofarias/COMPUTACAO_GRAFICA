#include "../../headers/data/Face.h"


Face::Face() {}
Face::~Face() {
	vertices.clear();
	vertices.shrink_to_fit();
	
    normais.clear();
	normais.shrink_to_fit();
	
    textures.clear();
	textures.shrink_to_fit();
}

void Face::addVerticeId(int idVertice) {
    this->vertices.push_back(idVertice);
}

void Face::addNormalId(int idNormal) {
    this->normais.push_back(idNormal);
}

void Face::addTextureId(int idTexture) {
    this->textures.push_back(idTexture);
}
