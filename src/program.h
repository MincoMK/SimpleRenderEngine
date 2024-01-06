#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

class Program {
public:
    GLuint id;
    char* data;
    int length;
    GLenum binaryFormat;

    Program(char* data, int length, GLenum binaryFormat);
    
    GLuint loadProgram();
    void use();
    void setMat4(string name, mat4 value);
    void setMat3(string name, mat3 value);
    void setMat2(string name, mat2 value);
    void setVec4(string name, vec4 value);
    void setVec3(string name, vec3 value);
    void setVec2(string name, vec2 value);
    void setFloat(string name, float value);
    void setInt(string name, int value);
    void setBool(string name, bool value);
    void setVec3Array(string name, vec3* value, int length);

    static Program fromShader(string vertexShader, string fragmentShader);
    static Program fromFile(string vertexShaderPath, string fragmentShaderPath);
    static Program empty();
};
