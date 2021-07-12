#pragma once

#include <iostream>
#include <string>
#include <vulkan/vulkan.h>

struct DebugMessenger
{
private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
        VkDebugUtilsMessageTypeFlagsEXT msgType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    );

    VkDebugUtilsMessengerEXT callback = nullptr;
    const VkInstance& instance;

public:
    DebugMessenger(const VkInstance& instance, const VkDebugUtilsMessengerCreateInfoEXT* createInfoExt);
    ~DebugMessenger();
    
    static VkResult CreateDebugUtilsMessengerEXT(
        const VkInstance&                           instance, 
        const VkDebugUtilsMessengerCreateInfoEXT*   createInfoExt, 
        const VkAllocationCallbacks*                pAllocator, 
        VkDebugUtilsMessengerEXT*                   pCallback
    );

    static void DestroyDebugUtilsMessengerEXT(const VkInstance& instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
    static void PopulateDebugUtilsMessengerCreateInfoEXT(VkDebugUtilsMessengerCreateInfoEXT* createInfo);
};
