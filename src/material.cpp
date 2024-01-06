#include "material.h"
#include <GL/glew.h>
#include <iostream>

Material::Material(Program program, NormalType normalType): program(program)
{
    this->program = program;
    this->normalType = normalType;
}

Material Material::empty() {
    return Material(Program::empty(), NormalType::FLAT);
}
