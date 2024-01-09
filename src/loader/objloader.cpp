#include "loader/objloader.h"
#include "triangle.h"
#include <fstream>
#include <iostream>
#include <sstream>

Mesh loadObj(string filename) {
    vector<vec3> tmpVertices;
    vector<vec2> tmpUvs;
    vector<vec3> tmpNormals;

    vector<Triangle> triangles;
    vector<Index> indices;
    vector<vec3> normals;
    vector<vec2> uvs;

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string prefix;
        iss >> prefix;

        if (prefix == "v") {
            vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            tmpVertices.push_back(vertex);
        } else if (prefix == "vt") {
            vec2 uv;
            iss >> uv.x >> uv.y;
            tmpUvs.push_back(uv);
        } else if (prefix == "vn") {
            vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "f") {
            string v1, v2, v3;
            iss >> v1 >> v2 >> v3;
            int vIndex1, vtIndex1, vnIndex1, vIndex2, vtIndex2, vnIndex2, vIndex3, vtIndex3, vnIndex3;
            sscanf(v1.c_str(), "%d/%d/%d", &vIndex1, &vtIndex1, &vnIndex1);
            sscanf(v2.c_str(), "%d/%d/%d", &vIndex2, &vtIndex2, &vnIndex2);
            sscanf(v3.c_str(), "%d/%d/%d", &vIndex3, &vtIndex3, &vnIndex3);

            indices.push_back({vIndex1 - 1, vIndex2 - 1, vIndex3 - 1});
        }
    }

    for (int i = 0; i < indices.size(); i++) {
        vec3 pos1 = tmpVertices[indices[i].a];
        vec3 pos2 = tmpVertices[indices[i].b];
        vec3 pos3 = tmpVertices[indices[i].c];
        vec2 uv1 = tmpUvs[indices[i].a];
        vec2 uv2 = tmpUvs[indices[i].b];
        vec2 uv3 = tmpUvs[indices[i].c];
        Triangle triangle = Triangle(pos1, pos2, pos3);
        uvs.push_back(uv1);
        uvs.push_back(uv2);
        uvs.push_back(uv3);
        triangles.push_back(triangle);
    }

    file.close();
    return Mesh(triangles, indices, normals, uvs);
}
