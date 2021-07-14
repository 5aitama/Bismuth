#pragma once

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <vector>

#include "debug_msg.h"
#include "queue_family_indices.h"


/**
 * @brief Contains all data that was necessary for a Vulkan Application.
 */
struct VulkanApp {
    const char* app_name;
    GLFWwindow* window = nullptr;

    /** 
     * All debug data needed was here... so be
     * carefull when you use them (don't forgot 
     * the NDEBUG def)
     */
    #ifndef NDEBUG
    VkDebugUtilsMessengerEXT callback = VK_NULL_HANDLE;
    #endif

    VulkanUtils::QueueFamilyIndices indices;

    std::vector<const char*> instanceExtensions;
	std::vector<const char*> instanceLayer;
    std::vector<const char*> deviceExtensions;

    std::vector<VkImage>        swapChainImages;
    std::vector<VkImageView>    swapChainImageViews;
    std::vector<VkFramebuffer>  swapChainFramebuffers;
    VkFormat                    swapChainImageFormat;
    VkExtent2D                  swapChainExtent;

    VkInstance          instance        = VK_NULL_HANDLE;
    VkPhysicalDevice    physicalDevice  = VK_NULL_HANDLE;
    VkDevice            device          = VK_NULL_HANDLE;
    VkQueue             graphicsQueue   = VK_NULL_HANDLE;
    VkQueue             presentQueue    = VK_NULL_HANDLE;
    VkSurfaceKHR        surface         = VK_NULL_HANDLE;
    VkSwapchainKHR      swapChain       = VK_NULL_HANDLE;

    VkRenderPass        renderPass          = VK_NULL_HANDLE;
    VkPipelineLayout    pipelineLayout      = VK_NULL_HANDLE;
    VkPipeline          graphicsPipeline    = VK_NULL_HANDLE;

    VkCommandPool       commandPool     = VK_NULL_HANDLE;

    std::vector<VkCommandBuffer> commandBuffers;

    VulkanApp(const char* app_name);
    ~VulkanApp();
};