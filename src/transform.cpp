#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <algorithm>
#include <iostream>

using namespace glm;

Transform::Transform(vec3 pos, vec3 rot, vec3 scale)
{
    this->translation = pos;
    this->rotation = rot;
    this->scale = scale;
    this->parent = nullptr;
}

mat4 Transform::getLocalModelMatrix()
{
    return translate(mat4(1), translation) * eulerAngleXYZ(radians(rotation.x), radians(rotation.y), radians(rotation.z)) * glm::scale(mat4(1), scale);
}

mat4 Transform::getWorldModelMatrix()
{
    mat4 modelMatrix = mat4(1);
    if (parent != nullptr) {
        modelMatrix = parent->getWorldModelMatrix();
    }

    modelMatrix = modelMatrix * getLocalModelMatrix();

    return modelMatrix;
}

vec3 Transform::getForward()
{
    return rotateAxis(vec3(0, 0, 1));
}

vec3 Transform::getUp()
{
    return rotateAxis(vec3(0, 1, 0));
}

vec3 Transform::rotateAxis(vec3 axis) {
    float prz = 0;
    float prx = 0;
    float pry = 0;
    if (parent != nullptr) {
        prz = parent->rotation.z;
        prx = parent->rotation.x;
        pry = parent->rotation.y;
    }
    auto rotMatrix = mat4(1);
    rotMatrix = glm::rotate(rotMatrix, radians(prz), vec3(0, 0, 1));
    rotMatrix = glm::rotate(rotMatrix, radians(prx), vec3(1, 0, 0));
    rotMatrix = glm::rotate(rotMatrix, radians(pry), vec3(0, 1, 0));

    return normalize(vec3(rotMatrix * vec4(axis, 1)));
}

void Transform::setParent(Transform *parent)
{
    if (this->parent != nullptr) {
        auto it = find(this->parent->children.begin(), this->parent->children.end(), this);
        if (it != this->parent->children.end()) {
            this->parent->children.erase(it);
        }
    }
    this->parent = parent;
    if (parent != nullptr) {
        parent->children.push_back(this);
    }
}

Transform Transform::childOf(Transform *parent)
{
    Transform t = Transform::identity();
    t.setParent(parent);
    return t;
}

Transform Transform::identity()
{
    return Transform(vec3(0), vec3(0), vec3(1));
}
