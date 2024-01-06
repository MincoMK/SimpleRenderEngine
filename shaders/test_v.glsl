#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMat;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 pos;
out vec3 normal;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    pos = vec3(view * model * vec4(aPos, 1.0));
    normal = aNormal * mat3(normalMat);
}
