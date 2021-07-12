#include "window.h"

Window::Window(const char* title, const uint32_t& width, const uint32_t& height) {
    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Failed to initialize glfw");

    // Tell GLFW that we not work with OpenGL
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Tell GLFW that the window must not be resizable
    // because this is a bit more complex to handle it
    // with vulkan and I don't have the knowledge to do
    // that for now.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Window::GetGlfwWindow() {
	return window;
}

const void Window::Loop() const {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}
