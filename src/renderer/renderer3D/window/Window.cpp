#include "Window.hpp"
#include <iostream>
#include "GLFW/glfw3.h"

Window::Window(int width, int height)
    : _width(width), _height(height)
{
    if (!glfwInit())
    {
        throw -1; // Initialization failed
    }

    window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw -1; // Window creation failed
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (window)
        {
            window->onKeyPress(w, key, scancode, action, mods); // Call the key press function
        }
    };

    glfwSetKeyCallback(window, func); // Set the key callback function
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (_onKeyPress)
        {
            _onKeyPress(key); // Call the left key press function
        }
    }
}
