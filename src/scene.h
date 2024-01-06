#pragma once

#include <vector>

#include "camera.h"
#include "object.h"
#include "light.h"
using namespace std;

class Scene {
public:
    vector<Object*> objects;
    vector<Light*> lights;
    vector<Camera*> cameras;
    int activeCameraIndex;

    Scene();
    void render();
    void setActiveCamera(int index);
    Camera getActiveCamera();
};
