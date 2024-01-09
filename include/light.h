#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Light {
public:
    vec3 pos;
    vec3 color;
    float intensity;

    Light(vec3 pos, vec3 color, float intensity);
};
