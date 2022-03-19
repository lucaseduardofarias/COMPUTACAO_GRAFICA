#ifndef FACE_H
#define FACE_H

#include <vector>

using namespace std;

class Face {

private:
    vector<int> vertices;
    vector<int> normais;
    vector<int> textures;

public:

    Face();
    ~Face();

    void addVerticeId(int idVertice);
    void addNormalId(int idNormal);
    void addTextureId(int idTexture);


    vector<int>& getVertices() {
        return vertices;
    }

    vector<int>& getNormais() {
        return normais;
    }

    vector<int>& getTextures() {
        return textures;
    }
};
#endif
