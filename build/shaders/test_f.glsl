#version 330 core

uniform vec3 lightPos;
uniform vec3 objectColor;

out vec4 FragColor;

in vec3 pos;
in vec3 normal;

void main() {
    // draw red square around the vertex
    float ambientStrength = 0.1f;
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - pos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0f);
}
