#pragma once

#include <functional>
#include <utility>
#include <vector>
#include "GLFW/glfw3.h"

class Scene; // Forward declaration of Scene class
class Window {
    GLFWwindow* window;

    int _width;
    int _height;

    const char* _title = "OpenGL Window";

    std::function<void(int)> _onKeyPress = nullptr;

public:
    Window(int width, int height);
    ~Window();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    GLFWwindow* getWindow() { return window; }

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

    void setOnKeyPress(std::function<void(int)> func) { _onKeyPress = std::move(func); }
};