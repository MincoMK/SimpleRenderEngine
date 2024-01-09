#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Triangle {
public:
    vec3 pos[3];

    Triangle(vec3 p1, vec3 p2, vec3 p3);
    vec3 getNormal();
};
