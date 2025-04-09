#define GLFW_INCLUDE_NONE
#include "Window.hpp"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "utils/errors/Exception.hpp"

Window::Window(int width, int height)
    : _width(width), _height(height)
{
    if (!glfwInit())
    {
        throw WindowException("Failed to initialize GLFW"); // Initialization failed
    }

    window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw WindowException("Failed to create GLFW window"); // Window creation failed
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    auto keyCallback = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (window)
        {
            window->onKeyPress(w, key, scancode, action, mods); // Call the key press function
        }
    };

    auto sizeCallback = [](GLFWwindow* w, int width, int height) {
        auto* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (window)
        {
            window->onSizeChange(width, height); // Call the size change function
        }
    };

    glfwSetKeyCallback(window, keyCallback);         // Set the key callback function
    glfwSetWindowSizeCallback(window, sizeCallback); // Set the size callback function
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

void Window::onSizeChange(int width, int height)
{
    _width  = width;
    _height = height;
    glad_glViewport(0, 0, _width, _height); // Set the viewport size
}
