#pragma once

#include "GLFW/glfw3.h"

class Window {
    GLFWwindow* window;

    int _width;
    int _height;

    const char* _title = "OpenGL Window";

public:
    Window(int width, int height);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    GLFWwindow* getWindow() { return window; }
};