#include "mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Mesh::Mesh(vector<Triangle> triangles)
{
    this->triangles = triangles;
    this->normals = vector<vec3>();
    this->indices = vector<Index>();
    this->uvs = vector<vec2>();
}

Mesh::Mesh(vector<Triangle> triangles, vector<Index> indices, vector<vec3> normals, vector<vec2> uvs)
{
    this->triangles = triangles;
    this->normals = normals;
    this->indices = indices;
    this->uvs = uvs;
}

vector<float> Mesh::getVertices()
{
    vector<float> vertices;
    for (int i = 0; i < triangles.size(); i++) {
        vertices.push_back(triangles[i].pos[0].x);
        vertices.push_back(triangles[i].pos[0].y);
        vertices.push_back(triangles[i].pos[0].z);
        vertices.push_back(triangles[i].pos[1].x);
        vertices.push_back(triangles[i].pos[1].y);
        vertices.push_back(triangles[i].pos[1].z);
        vertices.push_back(triangles[i].pos[2].x);
        vertices.push_back(triangles[i].pos[2].y);
        vertices.push_back(triangles[i].pos[2].z);
    }
    return vertices;
}

vector<float> Mesh::getNormals(NormalType normalType)
{
    vector<float> normals;
    if (normalType == SMOOTH) {
        if (this->normals.size() == 0) {
            cerr << "No normals provided" << endl;
            throw "No normals provided";
        }
        for (int i = 0; i < triangles.size(); i++) {
            normals.push_back(this->normals[i].x);
            normals.push_back(this->normals[i].y);
            normals.push_back(this->normals[i].z);
            normals.push_back(this->normals[i].x);
            normals.push_back(this->normals[i].y);
            normals.push_back(this->normals[i].z);
            normals.push_back(this->normals[i].x);
            normals.push_back(this->normals[i].y);
            normals.push_back(this->normals[i].z);
        }
    } else if (normalType == FLAT) {
        for (int i = 0; i < triangles.size(); i++) {
            vec3 normal = triangles[i].getNormal();
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
        }
    }

    return normals;
}

vector<unsigned int> Mesh::getIndices()
{
    vector<unsigned int> ret;
    for (int i = 0; i < this->indices.size(); i++) {
        ret.push_back(this->indices[i].a);
        ret.push_back(this->indices[i].b);
        ret.push_back(this->indices[i].c);
    }
    return ret;
}

Mesh Mesh::cube()
{
    vector<Triangle> triangles = {
        Triangle(vec3(-1.0f,-1.0f,-1.0f), vec3(-1.0f,-1.0f, 1.0f), vec3(-1.0f, 1.0f, 1.0f)),
        Triangle(vec3(1.0f, 1.0f,-1.0f), vec3(-1.0f,-1.0f,-1.0f), vec3(-1.0f, 1.0f,-1.0f)),
        Triangle(vec3(1.0f,-1.0f, 1.0f), vec3(-1.0f,-1.0f,-1.0f), vec3(1.0f,-1.0f,-1.0f)),
        Triangle(vec3(1.0f, 1.0f,-1.0f), vec3(1.0f,-1.0f,-1.0f), vec3(-1.0f,-1.0f,-1.0f)),
        Triangle(vec3(-1.0f,-1.0f,-1.0f), vec3(-1.0f, 1.0f, 1.0f), vec3(-1.0f, 1.0f,-1.0f)),
        Triangle(vec3(1.0f,-1.0f, 1.0f), vec3(-1.0f,-1.0f, 1.0f), vec3(-1.0f,-1.0f,-1.0f)),
        Triangle(vec3(-1.0f, 1.0f, 1.0f), vec3(-1.0f,-1.0f, 1.0f), vec3(1.0f,-1.0f, 1.0f)),
        Triangle(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f,-1.0f,-1.0f), vec3(1.0f, 1.0f,-1.0f)),
        Triangle(vec3(1.0f,-1.0f,-1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f,-1.0f, 1.0f)),
        Triangle(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f,-1.0f), vec3(-1.0f, 1.0f,-1.0f)),
        Triangle(vec3(1.0f, 1.0f, 1.0f), vec3(-1.0f, 1.0f,-1.0f), vec3(-1.0f, 1.0f, 1.0f)),
        Triangle(vec3(1.0f, 1.0f, 1.0f), vec3(-1.0f, 1.0f, 1.0f), vec3(1.0f,-1.0f, 1.0f))
    };
    return Mesh(triangles);
}

Mesh Mesh::icosahedron()
{
    auto t = (1.0f + sqrt(5.0f)) / 2.0f;

    vector<Triangle> triangles = {
        Triangle(vec3(-1, t, 0), vec3(1, t, 0), vec3(0, 1, t)),
        Triangle(vec3(-1, t, 0), vec3(0, 1, t), vec3(0, 1, -t)),
        Triangle(vec3(-1, t, 0), vec3(0, 1, -t), vec3(-t, 0, -1)),
        Triangle(vec3(-1, t, 0), vec3(-t, 0, -1), vec3(-t, 0, 1)),
        Triangle(vec3(-1, t, 0), vec3(-t, 0, 1), vec3(0, 1, t)),
        Triangle(vec3(1, t, 0), vec3(0, 1, t), vec3(t, 0, 1)),
        Triangle(vec3(1, t, 0), vec3(t, 0, 1), vec3(t, 0, -1)),
        Triangle(vec3(1, t, 0), vec3(t, 0, -1), vec3(0, 1, -t)),
        Triangle(vec3(1, t, 0), vec3(0, 1, -t), vec3(0, 1, t)),
        Triangle(vec3(1, -t, 0), vec3(0, -1, t), vec3(0, -1, -t)),
        Triangle(vec3(1, -t, 0), vec3(0, -1, -t), vec3(t, 0, -1)),
        Triangle(vec3(1, -t, 0), vec3(t, 0, -1), vec3(t, 0, 1)),
        Triangle(vec3(1, -t, 0), vec3(t, 0, 1), vec3(0, -1, t)),
        Triangle(vec3(-1, -t, 0), vec3(0, -1, t), vec3(-t, 0, 1)),
        Triangle(vec3(-1, -t, 0), vec3(-t, 0, 1), vec3(-t, 0, -1)),
        Triangle(vec3(-1, -t, 0), vec3(-t, 0, -1), vec3(0, -1, -t)),
        Triangle(vec3(-1, -t, 0), vec3(0, -1, -t), vec3(0, -1, t)),
        Triangle(vec3(0, 1, t), vec3(0, -1, t), vec3(t, 0, 1)),
        Triangle(vec3(0, 1, -t), vec3(t, 0, -1), vec3(0, -1, -t)),
        Triangle(vec3(0, 1, t), vec3(t, 0, 1), vec3(1, t, 0)),
        Triangle(vec3(0, 1, t), vec3(1, t, 0), vec3(0, 1, -t)),
        Triangle(vec3(0, 1, -t), vec3(0, -1, -t), vec3(-1, -t, 0)),
        Triangle(vec3(0, 1, -t), vec3(-1, -t, 0), vec3(0, -1, t)),
        Triangle(vec3(0, -1, t), vec3(-1, -t, 0), vec3(-t, 0, 1)),
        Triangle(vec3(0, -1, t), vec3(-t, 0, 1), vec3(0, 1, t)),
        Triangle(vec3(0, -1, -t), vec3(0, 1, -t), vec3(-t, 0, -1)),
        Triangle(vec3(0, -1, -t), vec3(-t, 0, -1), vec3(-1, -t, 0)),
        Triangle(vec3(0, -1, -t), vec3(-1, -t, 0), vec3(0, -1, t)),
        Triangle(vec3(0, -1, -t), vec3(0, 1, -t), vec3(1, t, 0)),
        Triangle(vec3(0, -1, -t), vec3(1, t, 0), vec3(t, 0, -1)),
        Triangle(vec3(0, 1, t), vec3(0, -1, t), vec3(-1, -t, 0)),
        Triangle(vec3(0, 1, t), vec3(-1, -t, 0), vec3(-t, 0, 1)),
        Triangle(vec3(0, -1, t), vec3(0, -1, -t), vec3(t, 0, -1)),
        Triangle(vec3(0, -1, t), vec3(t, 0, -1), vec3(1, -t, 0)),
        Triangle(vec3(0, -1, t), vec3(1, -t, 0), vec3(0, 1, t)),
        Triangle(vec3(0, -1, -t), vec3(0, 1, -t), vec3(1, t, 0)),
        Triangle(vec3(0, -1, -t), vec3(1, t, 0), vec3(t, 0, 1)),
        Triangle(vec3(0, 1, -t), vec3(0, 1, t), vec3(-t, 0, 1)),
        Triangle(vec3(0, 1, -t), vec3(-t, 0, 1), vec3(-1, t, 0)),
        Triangle(vec3(0, 1, -t), vec3(-1, t, 0), vec3(0, -1, -t)),
        Triangle(vec3(0, 1, -t), vec3(0, -1, -t), vec3(1, -t, 0)),
        Triangle(vec3(0, 1, t), vec3(0, 1, -t), vec3(1, -t, 0)),
        Triangle(vec3(0, 1, t), vec3(1, -t, 0), vec3(t, 0, 1)),
        Triangle(vec3(0, 1, t), vec3(t, 0, 1), vec3(-1, t, 0)),
        Triangle(vec3(0, -1, t), vec3(0, -1, -t), vec3(-1, t, 0)),
        Triangle(vec3(0, -1, t), vec3(-1, t, 0), vec3(-t, 0, -1)),
        Triangle(vec3(0, -1, t), vec3(-t, 0, -1), vec3(1, -t, 0)),
        Triangle(vec3(0, -1, -t), vec3(0, -1, t), vec3(1, -t, 0)),
        Triangle(vec3(0, -1, -t), vec3(1, -t, 0), vec3(t, 0, -1)),
        Triangle(vec3(0, -1, -t), vec3(t, 0, -1), vec3(-1, t, 0))
    };

    return Mesh(triangles);
}

Mesh Mesh::plane()
{
    vector<Triangle> triangles = {
        Triangle(vec3(-1.0f, 0.0f, -1.0f), vec3(-1.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 1.0f)),
        Triangle(vec3(-1.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, -1.0f))
    };
    return Mesh(triangles);
}

Mesh Mesh::empty()
{
    return Mesh(vector<Triangle>());
}
