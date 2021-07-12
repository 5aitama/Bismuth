#include "vulkan_app.h"

VulkanApp::VulkanApp(const char* app_name) : app_name(app_name) { };

VulkanApp::~VulkanApp() {
    
    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    DebugMessenger::DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);
    vkDestroyInstance(instance, nullptr);
};