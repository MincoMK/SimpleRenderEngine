#pragma once
#include "object.h"
#include "scene.h"
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

// AnimationCallback is a function that takes float deltaTime and return void
typedef std::function<void(float)> AnimationCallback;

using namespace std;

class Window {
public:
    GLFWwindow *window;
    int width;
    int height;
    string title;
    Scene* scene;
    
    Window(int width, int height, string title);
    void init();
    void setScene(Scene *scene);
    void startEventLoop(AnimationCallback animationCallback);
};
