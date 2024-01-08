#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <iostream>
#include "object.h"
#include "scene.h"

Object::Object(Mesh mesh, Transform transform, Material material): mesh(mesh), transform(transform), material(material)
{
    isEmpty = false;
}

Object Object::empty() {
    Object obj = Object(Mesh::empty(), Transform::identity(), Material::empty());
    obj.isEmpty = true;
    return obj;
}

void Object::draw(Scene* scene) {
    if (isEmpty)
        return;
    auto program = this->material.program;
    auto cam = scene->getActiveCamera();
    auto modelMatrix = transform.getWorldModelMatrix();
    program.setMat4("model", modelMatrix);
    program.setMat4("view", cam.getViewMatrix());
    program.setMat4("projection", cam.getProjectionMatrix());
    program.setMat4("normalMat", transpose(inverse(cam.getViewMatrix() * modelMatrix)));
    program.use();

    auto lightPositions = vector<vec3>();
    auto lightColors = vector<vec3>();
    for (int i = 0; i < scene->lights.size(); i++) {
        lightPositions.push_back(scene->lights[i]->pos);
        lightColors.push_back(scene->lights[i]->color);
    }
    program.setVec3Array("lightPositions", lightPositions.data(), lightPositions.size());
    program.setVec3Array("lightColors", lightColors.data(), lightColors.size());

    GLuint VAO, VBO, EBO, NBO, UBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &NBO);
    glGenBuffers(1, &UBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size() * sizeof(unsigned int), mesh.getIndices().data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(float), mesh.getVertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getNormals(material.normalType).size() * sizeof(float), mesh.getNormals(material.normalType).data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, UBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.uvs.size() * sizeof(float), mesh.uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLES, 0, mesh.triangles.size() * 3);
}
