#include "vulkan_app.h"

VulkanApp::VulkanApp(const char* app_name) : app_name(app_name) {
};

VulkanApp::~VulkanApp() {

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (renderFinishedSemaphores[i] != VK_NULL_HANDLE) {
            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        }

        if (imageAvailableSemaphores[i] != VK_NULL_HANDLE) {
            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        }

        if (inFlightFences[i] != VK_NULL_HANDLE) {
            vkDestroyFence(device, inFlightFences[i], nullptr);
        }
    }

    if (commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    if (graphicsPipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(device, graphicsPipeline, nullptr);
    }

    if (pipelineLayout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    }

    if (renderPass != VK_NULL_HANDLE) {
        vkDestroyRenderPass(device, renderPass, nullptr);
    }
    
    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    if (swapChain != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device, swapChain, nullptr);
    }

    if (device != VK_NULL_HANDLE) {
        vkDestroyDevice(device, nullptr);
    }

    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }

    if (callback != VK_NULL_HANDLE) {
        DebugMessenger::DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);
    }

    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
    }
};