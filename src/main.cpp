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
    
    Object camWrapper = Object::empty();
    scene.objects.push_back(&camWrapper);
    Camera camera = Camera(Transform::childOf(&camWrapper.transform), 90, 800.0f / 600.0f, 0.1f, 100.0f, ProjectionType::PERSPECTIVE);
    scene.cameras.push_back(&camera);
    scene.setActiveCamera(0);

    // init light
    Light light = Light(vec3(0, 0, 0), vec3(1, 1, 1), 1);
    scene.lights.push_back(&light);

    Mesh ico = loadObj("models/ico.obj");
    Program p = Program::fromFile("shaders/test_v.glsl", "shaders/test_f.glsl");
    p.setVec3("objectColor", vec3(1, 0, 0));
    Material m = Material(p, NormalType::FLAT);
    Object o = Object(ico, Transform::identity(), m);
    scene.objects.push_back(&o);
    
    win.setScene(&scene);
    auto lastMouseX = 0.0;
    auto lastMouseY = 0.0;
    glfwGetCursorPos(win.window, &lastMouseX, &lastMouseY);
    win.startEventLoop([&](float deltaTime) {
        double mouseX, mouseY;
        glfwGetCursorPos(win.window, &mouseX, &mouseY);
        auto mouseDeltaX = mouseX - lastMouseX;
        auto mouseDeltaY = mouseY - lastMouseY;
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        camera.transform.rotation.x -= mouseDeltaY * deltaTime * 20;
        camWrapper.transform.rotation.y -= mouseDeltaX * deltaTime * 20;

        if (glfwGetKey(win.window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.transform.translation += camera.transform.getForward() * deltaTime * 5.0f;
        }

        if (glfwGetKey(win.window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.transform.translation -= camera.transform.getForward() * deltaTime * 5.0f;
        }

        if (glfwGetKey(win.window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.transform.translation -= normalize(cross(camera.transform.getForward(), camera.transform.getUp())) * deltaTime * 5.0f;
        }

        if (glfwGetKey(win.window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.transform.translation += normalize(cross(camera.transform.getForward(), camera.transform.getUp())) * deltaTime * 5.0f;
        }
    });
    return 0;
}

