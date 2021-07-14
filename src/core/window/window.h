#pragma once

#include <iostream>

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include "../vulkan/vulkan_app.h"

struct Window {
private:
	GLFWwindow* window = nullptr;
	size_t currentFrame = 0;

public:
	/**
	 * @brief Create new window.
	 * 
	 * @param title The window title.
	 * @param width The window width.
	 * @param height The window height.
	 */
	Window(const char* title, const uint32_t& width, const uint32_t& height);
	~Window();

	/**
	 * @brief Return a pointer to the GLFWwindow in the current window. 
	 */
	GLFWwindow* GetGlfwWindow();

	/**
	 * @brief Start the window's main loop.
	 */
	const void Loop(VulkanApp& app);

	const void DrawFrame(VulkanApp& app);
};