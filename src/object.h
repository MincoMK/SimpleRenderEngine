#pragma once
#include <glm/glm.hpp>
#include "mesh.h"
#include "material.h"
#include "transform.h"

using namespace glm;

class Scene;

class Object {
public:
    Mesh mesh;
    Transform transform;
    Material material;
    bool isEmpty;

    Object(Mesh mesh, Transform transform, Material material);
    void draw(Scene *scene);

    static Object empty();
};
