#version 330 core

uniform vec3 lightPositions[10];
uniform vec3 lightColors[10];
uniform vec3 objectColor;

out vec4 FragColor;

in vec3 pos;
in vec3 normal;

void main() {
    // draw red square around the vertex

    vec3 result = vec3(0.0f);
    for (int i = 0; i < 10; i++) {
        // ambient
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColors[i];

        // diffuse
        vec3 lightDir = normalize(lightPositions[i] - pos);
        float diff = max(dot(normal, lightDir), 0.0f);
        vec3 diffuse = diff * lightColors[i];

        // specular
        float specularStrength = 0.5f;
        vec3 viewDir = normalize(-pos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
        vec3 specular = specularStrength * spec * lightColors[i];

        // shadow
        vec3 lightPos = lightPositions[i];
        vec3 fragPos = pos;
        vec3 lightDir2 = normalize(lightPos - fragPos);
        float shadow = 0.0f;
        vec3 fragPos2 = fragPos + normal * 0.001f;
        float bias = 0.001f;
        float maxDistance = 100.0f;
        int shadowSamples = 10;
        float sampleStep = maxDistance / float(shadowSamples);
        for (int i = 0; i < shadowSamples; i++) {
            float distance = length(lightPos - fragPos2);
            if (distance < length(lightPos - fragPos)) {
                shadow += 1.0f;
            }
            fragPos2 += lightDir2 * sampleStep;
        }
        shadow /= float(shadowSamples);
        shadow = clamp(shadow, 0.0f, 1.0f);

        // result
        result += (ambient + (1.0f - shadow) * (diffuse + specular)) * objectColor;
    }

    FragColor = vec4(result, 1.0f);
}
