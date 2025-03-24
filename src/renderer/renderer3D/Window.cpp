#include "Window.hpp"

Window::Window(int width, int height)
    : _width(width), _height(height) {}

Window::~Window() {}

void Window::create()
{
    window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
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
