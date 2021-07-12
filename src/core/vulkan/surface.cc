#include "surface.h"

using namespace VulkanUtils;

void Surface::Init(VulkanApp& app, Window& window) {
    if (glfwCreateWindowSurface(app.instance, window.GetGlfwWindow(), nullptr, &app.surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface !");
    }
}