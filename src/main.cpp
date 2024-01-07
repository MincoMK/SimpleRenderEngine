#include "object.h"
#include "scene.h"
#include "mesh.h"
#include "material.h"
#include "program.h"
#include "window.h"
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>
#include "loader/objloader.h"

using namespace std;

int main() {
    Window win = Window(800, 600, "Hello World");
    win.init();
    
    Scene scene = Scene();
    
    Program p = Program::fromFile("shaders/test_v.glsl", "shaders/test_f.glsl");
    
    Object cameraObject = Object::empty();
    cameraObject.transform = Transform(vec3(5, 5, 5), vec3(0, 0, 0), vec3(1));
    scene.objects.push_back(&cameraObject);
    Camera camera = Camera(Transform(vec3(5,5,5),vec3(0),vec3(1)), 90, 800.0f / 600.0f, 0.1f, 100.0f, ProjectionType::PERSPECTIVE);
    scene.cameras.push_back(&camera);
    scene.setActiveCamera(0);

    cameraObject.transform.rotation.y = 0;
    camera.transform.rotation.x = 0;

    // init light
    Light light = Light(vec3(5, 5, 5), vec3(1, 1, 1), 1);
    scene.lights.push_back(&light);

    Mesh ico = loadObj("models/ico.obj");
    auto icoP = p.clone();
    icoP.setVec3("objectColor", vec3(1, 0, 0));
    Material icoM = Material(icoP, NormalType::FLAT);
    Object icoO = Object(ico, Transform(vec3(3,3,3), vec3(0), vec3(1)), icoM);
    scene.objects.push_back(&icoO);

    Mesh plane = Mesh::plane();
    auto planeP = p.clone();
    planeP.setVec3("objectColor", vec3(0, 1, 0));
    Material planeM = Material(planeP, NormalType::FLAT);
    Object planeO = Object(plane, Transform(vec3(0), vec3(0), vec3(5)), planeM);
    scene.objects.push_back(&planeO);
    
    win.setScene(&scene);
    auto lastMouseX = 0.0;
    auto lastMouseY = 0.0;
    glfwGetCursorPos(win.window, &lastMouseX, &lastMouseY);
    win.startEventLoop([&](float deltaTime) {
        auto cursorX = 0.0;
        auto cursorY = 0.0;
        glfwGetCursorPos(win.window, &cursorX, &cursorY);
        auto deltaX = cursorX - lastMouseX;
        auto deltaY = cursorY - lastMouseY;
        lastMouseX = cursorX;
        lastMouseY = cursorY;

        camera.transform.rotation.y -= deltaX * deltaTime * 30;
        icoO.transform.rotation.y -= deltaX * deltaTime * 10;
        //camera.transform.rotation.x -= deltaY * deltaTime * 30;

        // set cursor to center
    });
    return 0;
}

