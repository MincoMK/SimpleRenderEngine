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

mat4 Transform::getTranslateMatrix()
{
    mat4 translateMatrix = mat4(1);
    if (parent != nullptr) {
        translateMatrix = parent->getTranslateMatrix();
    }

    auto forward = getForward();
    auto up = getUp();
    auto right = cross(forward, up);
    vec3 translationNew = forward * translation.z + up * translation.y + right * translation.x;

    translateMatrix = glm::translate(translateMatrix, translationNew);

    return translateMatrix;
}

mat4 Transform::getRotateMatrix()
{
    mat4 rotateMatrix = mat4(1);
    if (parent != nullptr) {
        rotateMatrix = parent->getRotateMatrix();
    }

    vec3 forward = getForward();
    vec3 up = getUp();
    vec3 right = cross(forward, up);

    rotateMatrix = glm::rotate(rotateMatrix, radians(rotation.x), right);
    rotateMatrix = glm::rotate(rotateMatrix, radians(rotation.y), up);
    rotateMatrix = glm::rotate(rotateMatrix, radians(rotation.z), forward);

    return rotateMatrix;
}

mat4 Transform::getScaleMatrix()
{
    mat4 scaleMatrix = mat4(1);
    if (parent != nullptr) {
        scaleMatrix = parent->getScaleMatrix();
    }

    scaleMatrix = glm::scale(scaleMatrix, scale);

    return scaleMatrix;
}

mat4 Transform::getModelMatrix()
{
    return getTranslateMatrix() * getRotateMatrix() * getScaleMatrix();
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
    auto rotMatrix = mat4(1);
    rotMatrix = glm::rotate(rotMatrix, radians(rotation.x), vec3(1, 0, 0));
    rotMatrix = glm::rotate(rotMatrix, radians(rotation.y), vec3(0, 1, 0));
    rotMatrix = glm::rotate(rotMatrix, radians(rotation.z), vec3(0, 0, 1));

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
