#include "vulkan_app.h"

VulkanApp::VulkanApp(const char* app_name) : app_name(app_name) {
};

VulkanApp::~VulkanApp() {
    
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