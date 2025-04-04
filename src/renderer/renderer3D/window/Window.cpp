#include "Window.hpp"

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
