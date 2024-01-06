#include "camera.h"
#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(Transform transform, float fov, float aspect, float near, float far, ProjectionType type): Object(Mesh::empty(), transform, Material::empty())
{
    
    this->fov = fov;
    this->aspectRatio = aspect;
    this->near = near;
    this->far = far;
    this->type = type;
}

mat4 Camera::getViewMatrix()
{
    return inverse(transform.getModelMatrix());
}

mat4 Camera::getProjectionMatrix()
{
    if (type == PERSPECTIVE) {
        return glm::perspective(radians(fov), aspectRatio, near, far);
    } else if (type == ORTHOGRAPHIC) {
        return ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, near, far);
    } else {
        throw "Invalid projection type";
    }
}
