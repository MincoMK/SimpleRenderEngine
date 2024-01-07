#include <iostream>
#include <fstream>
#include <sstream>
#include "program.h"

using namespace std;

Program::Program(char* data, int length, GLenum binaryFormat) {
    this->id = 2147483647;
    this->data = data;
    this->length = length;
    this->binaryFormat = binaryFormat;
    this->use();
}

GLuint Program::loadProgram()
{
    GLuint programHandle = glCreateProgram();
    glProgramBinary(programHandle, this->binaryFormat, this->data, this->length);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programHandle, 512, NULL, infoLog);
        throw infoLog;
    }
    this->id = programHandle;
    return programHandle;
}

void Program::use()
{
    if (this->length == 0) return;
    if (this->id == 2147483647) {
        this->loadProgram();
    }
    glUseProgram(this->id);
}

Program Program::fromShader(string vs, string fs) {
    const char* vertexShaderSource = vs.c_str();
    const char* fragmentShaderSource = fs.c_str();

    int success;
    char infoLog[512];
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw infoLog;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader); 
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw infoLog;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader); 
    glAttachShader(shaderProgram, fragmentShader); 
    glLinkProgram(shaderProgram); 

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        throw infoLog;
    }

    int programLength = 0;
    glGetProgramiv(shaderProgram, GL_PROGRAM_BINARY_LENGTH, &programLength);
    char* program = new char[programLength];
    GLenum binaryFormat;
    glGetProgramBinary(shaderProgram, programLength, NULL, &binaryFormat, program);

    return Program(program, programLength, binaryFormat);
}

Program Program::fromFile(string vertexShaderPath, string fragmentShaderPath) {
    // read file
    string vertexShaderSource;
    string fragmentShaderSource;
    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;
    vertexShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fragmentShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexShaderSource = vertexShaderStream.str();
        fragmentShaderSource = fragmentShaderStream.str();
    } catch (ifstream::failure e) {
        throw "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    return Program::fromShader(vertexShaderSource, fragmentShaderSource);
}

void Program::setMat4(string name, mat4 value) {
    this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Program::setMat3(string name, mat3 value) {
    this->use();
    glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Program::setMat2(string name, mat2 value) {
    this->use();
    glUniformMatrix2fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Program::setVec4(string name, vec4 value) {
    this->use();
    glUniform4fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void Program::setVec3(string name, vec3 value) {
    this->use();
    glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void Program::setVec2(string name, vec2 value) {
    this->use();
    glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}

void Program::setFloat(string name, float value) {
    this->use();
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}

void Program::setInt(string name, int value) {
    this->use();
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Program::setBool(string name, bool value) {
    this->use();
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Program::setVec3Array(string name, vec3* value, int length) {
    this->use();
    glUniform3fv(glGetUniformLocation(this->id, name.c_str()), length, &value[0][0]);
}

Program Program::empty() {
    return Program((char*)"", 0, GL_PROGRAM_BINARY_RETRIEVABLE_HINT);
}

Program Program::clone() {
    return Program(this->data, this->length, this->binaryFormat);
}
