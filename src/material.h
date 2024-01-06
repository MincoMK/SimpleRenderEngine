#pragma once

#include "program.h"
#include "enums.h"
#include <string>
#include <GL/glew.h>

using namespace std;

class Material {
public:
    Program program;
    NormalType normalType;
    
    Material(Program program, NormalType normalType);

    static Material empty();
};
