#pragma once

#include <functional>
#include <utility>
#include "GLFW/glfw3.h"

class Scene; // Forward declaration of Scene class
class Window {
    GLFWwindow* window;

    int _width;
    int _height;

    const char* _title = "OpenGL Window";

    std::function<void(int)>                           _onKeyPress   = nullptr;
    std::function<void(int, int)>                      _onSizeChange = nullptr;
    std::function<void(int, int, int, double, double)> _onMouseClick = nullptr;

public:
    Window(int width, int height);
    ~Window();

    // Getters for width and height
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

    // Setters for width and height
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }

    bool shouldClose();
    void swapBuffers();
    void pollEvents();

    GLFWwindow* getWindow() { return window; }

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onSizeChange(int width, int height);
    void onMouseClick(int button, int action, int mods, double xpos, double ypos);

    void setOnKeyPress(std::function<void(int)> func) { _onKeyPress = std::move(func); }
    void setOnMouseClick(std::function<void(int, int, int, double, double)> func) { _onMouseClick = std::move(func); }
    void setOnSizeChange(std::function<void(int, int)> func) { _onSizeChange = std::move(func); }
};