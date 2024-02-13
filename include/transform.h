#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

class Transform {
public:
    vec3 translation;
    vec3 rotation;
    vec3 scale;
    vector<Transform*> children;
    Transform *parent;

    Transform(vec3 translation, vec3 rotation, vec3 scale);

    mat4 getLocalModelMatrix();
    mat4 getWorldModelMatrix();

    vec3 getForward();
    vec3 getUp();
    vec3 rotateAxis(vec3 axis);

    void setParent(Transform *parent);

    static Transform identity();
    static Transform childOf(Transform *parent);
};
