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
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (windowPtr)
        {
            windowPtr->onKeyPress(w, key, scancode, action, mods); // Call the key press function
        }
    };

    glfwSetKeyCallback(window, keyCallback); // Set the key callback function

    auto sizeCallback = [](GLFWwindow* w, int width, int height) {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (windowPtr)
        {
            windowPtr->onSizeChange(width, height); // Call the size change function
        }
    };

    glfwSetWindowSizeCallback(window, sizeCallback); // Set the size callback function

    auto mouseCallback = [](GLFWwindow* w, int button, int action, int mods) {
        auto* windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(w));

        double xpos, ypos;
        glfwGetCursorPos(windowPtr->getWindow(), &xpos, &ypos);
        // Convert the mouse position to normalized device coordinates (NDC)
        double xPos = (2.0 * xpos) / windowPtr->_width - 1.0;
        double yPos = 1.0 - (2.0 * ypos) / windowPtr->_height; // Invert y coordinate

        if (windowPtr)
        {
            windowPtr->onMouseClick(button, action, mods, xPos, yPos); // Call the mouse click function
        }
    };

    glfwSetMouseButtonCallback(window, mouseCallback); // Set the mouse click callback function
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
    if (_onSizeChange)
    {
        _onSizeChange(_width, _height); // Call the size change function
    }
    glad_glViewport(0, 0, _width, _height); // Set the viewport size
}

void Window::onMouseClick(int button, int action, int mods, double xpos, double ypos)
{
    if (_onMouseClick)
    {
        _onMouseClick(button, action, mods, xpos, ypos); // Call the mouse click function
    }
}
