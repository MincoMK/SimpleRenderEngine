#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "window.h"

using namespace std;

Window::Window(int width, int height, string title)
{
    this->width = width;
    this->height = height;
    this->title = title;
}

void Window::init() {
    glfwInit();
    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Window::setScene(Scene* scene) {
    this->scene = scene;
}

void Window::startEventLoop(AnimationCallback animationCallback) {
    auto lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        auto time = glfwGetTime();
        auto deltaTime = time - lastTime;
        glClearColor(0, 0, 0, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        animationCallback(deltaTime / 1000.0f);

        scene->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
