#include "scene.h"
#include <iostream>

using namespace std;

Scene::Scene() {
    this->activeCameraIndex = -1;
}

void Scene::render()
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw(this);
    }
}

void Scene::setActiveCamera(int index)
{
    activeCameraIndex = index;
}

Camera Scene::getActiveCamera()
{
    if (activeCameraIndex < 0 || activeCameraIndex >= cameras.size())
    {
        throw "Invalid active camera index";
    }
    return *cameras[activeCameraIndex];
}
