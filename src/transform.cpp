#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>

Transform::Transform(vec3 pos, vec3 rot, vec3 scale)
{
    this->translation = pos;
    this->rotation = rot;
    this->scale = scale;
    this->parent = nullptr;
}

mat4 Transform::getModelMatrix()
{
    mat4 model = mat4(1.0f);
    auto translation = getWorldTranslation();
    auto rotation = getWorldRotation();
    model = translate(model, translation);
    model = rotate(model, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    model = rotate(model, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    model = rotate(model, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

vec3 Transform::getForward()
{
    mat4 rotationMatrix = mat4(1.0f);
    rotationMatrix = rotate(rotationMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
    return rotationMatrix * vec4(0.0f, 0.0f, -1.0f, 1.0f);
}

vec3 Transform::getUp()
{
    mat4 rotationMatrix = mat4(1.0f);
    rotationMatrix = rotate(rotationMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = rotate(rotationMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));
    return rotationMatrix * vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

vec3 Transform::getWorldForward()
{
    if (parent == nullptr) {
        return getForward();
    } else {
        return parent->getWorldForward() + getForward();
    }
}

vec3 Transform::getWorldUp()
{
    if (parent == nullptr) {
        return getUp();
    } else {
        return parent->getWorldUp() + getUp();
    }
}

Transform Transform::identity()
{
    return Transform(vec3(0.0f), vec3(0.0f), vec3(1.0f));
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

vec3 Transform::getWorldTranslation()
{
    if (parent == nullptr) {
        return translation;
    } else {
        return parent->getWorldTranslation() + translation;
    }
}

vec3 Transform::getWorldRotation()
{
    if (parent == nullptr) {
        return rotation;
    } else {
        return parent->getWorldRotation() + rotation;
    }
}

vec3 Transform::getWorldScale()
{
    if (parent == nullptr) {
        return scale;
    } else {
        return parent->getWorldScale() * scale;
    }
}

Transform Transform::childOf(Transform *parent)
{
    Transform t = Transform::identity();
    t.setParent(parent);
    return t;
}
