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

const void Window::Loop(VulkanApp& app) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        DrawFrame(app);
    }

    vkDeviceWaitIdle(app.device);
}

const void Window::DrawFrame(VulkanApp& app) {

    uint32_t imageIndex;
    vkAcquireNextImageKHR(app.device, app.swapChain, UINT64_MAX, app.imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (app.imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(app.device, 1, &app.imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }

    app.imagesInFlight[imageIndex] = app.inFlightFences[currentFrame];

    VkSemaphore waitSemaphores[]        = { app.imageAvailableSemaphores[currentFrame] };
    VkPipelineStageFlags waitStages[]   = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    VkSemaphore signalSemaphores[]      = { app.renderFinishedSemaphores[currentFrame] };

    VkSubmitInfo submitInfo {
        .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount     = 1,
        .pWaitSemaphores        = waitSemaphores,
        .pWaitDstStageMask      = waitStages,
        .commandBufferCount     = 1,
        .pCommandBuffers        = &app.commandBuffers[imageIndex],
        .signalSemaphoreCount   = 1,
        .pSignalSemaphores      = signalSemaphores,
    };
    
    vkResetFences(app.device, 1, &app.inFlightFences[currentFrame]);

    if (vkQueueSubmit(app.graphicsQueue, 1, &submitInfo, app.inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("Failed to send command buffer !");
    }

    VkSwapchainKHR swapChains[] = { app.swapChain };

    VkPresentInfoKHR presentInfo {
        .sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores    = signalSemaphores,
        .swapchainCount     = 1,
        .pSwapchains        = swapChains,
        .pImageIndices      = &imageIndex,
        .pResults           = nullptr,
    };

    vkQueuePresentKHR(app.presentQueue, &presentInfo);
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
