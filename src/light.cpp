#include "light.h"

Light::Light(vec3 pos, vec3 color, float intensity)
{
    this->pos = pos;
    this->color = color;
    this->intensity = intensity;
}
