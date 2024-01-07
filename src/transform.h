#pragma once

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

    mat4 getModelMatrix();
    mat4 getTranslateMatrix();
    mat4 getRotateMatrix();
    mat4 getScaleMatrix();

    vec3 getForward();
    vec3 getUp();
    vec3 rotateAxis(vec3 axis);

    void setParent(Transform *parent);

    static Transform identity();
    static Transform childOf(Transform *parent);
};
