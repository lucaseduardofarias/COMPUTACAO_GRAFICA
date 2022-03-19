#ifndef GROUP_H
#define GROUP_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "Face.h"

using namespace std;

class Group {

private:
    vector<Face*> faces;
	vector<GLuint> vbos;
    GLuint vao;

public:

    Group();
    ~Group();

    Face* face(int id);
    int addFace(Face* face);

    vector<Face*>& getFaces() {
        return faces;
    };

    void addVBO(GLuint* vbo) {
		this->vbos.push_back(*vbo);
    }

    void setVAO(GLuint* vao) {
        this->vao = *vao;
    }

    GLuint& getVAO() {
        return this->vao;
    }

    int numVertices() {
        int sum = 0;
        for (auto& face : faces) {
            sum += face->getVertices().size();
        }
        return sum;
    }


};

#endif
