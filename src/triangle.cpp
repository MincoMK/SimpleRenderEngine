#include "triangle.h"

Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3)
{
    pos[0] = p1;
    pos[1] = p2;
    pos[2] = p3;
}

vec3 Triangle::getNormal()
{
    return normalize(cross(pos[1] - pos[0], pos[2] - pos[0]));
}
