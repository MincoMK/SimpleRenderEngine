#pragma once

#include <glm/glm.hpp>
#include "enums.h"
#include "object.h"
#include "transform.h"

using namespace glm;

class Camera: public Object {
public:
    float fov;
    float aspectRatio;
    float near;
    float far;
    ProjectionType type;

    Camera(Transform transform, float fov, float aspectRatio, float near, float far, ProjectionType type);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};
