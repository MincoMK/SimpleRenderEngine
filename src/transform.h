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

    vec3 getForward();
    vec3 getUp();

    void setParent(Transform *parent);
    vec3 getWorldTranslation();
    vec3 getWorldRotation();
    vec3 getWorldScale();
    vec3 getWorldForward();
    vec3 getWorldUp();

    static Transform identity();
    static Transform childOf(Transform *parent);
};
