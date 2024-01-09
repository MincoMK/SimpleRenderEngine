#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "triangle.h"
#include "enums.h"

using namespace std;
using namespace glm;

class Mesh {
public:
    vector<Triangle> triangles;
    vector<vec2> uvs;
    vector<vec3> normals;
    vector<Index> indices;

    Mesh(vector<Triangle> triangles);
    Mesh(vector<Triangle> triangles, vector<Index> indices, vector<vec3> normals, vector<vec2> uvs);
    vector<float> getVertices();
    vector<float> getNormals(NormalType normalType);
    vector<unsigned int> getIndices();

    static Mesh cube();
    static Mesh icosahedron();
    static Mesh plane();
    static Mesh empty();
};
