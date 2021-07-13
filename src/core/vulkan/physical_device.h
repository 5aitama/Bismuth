#pragma once

#include <iostream>
#include <exception>
#include <vulkan/vulkan.h>
#include <vector>

#include "vulkan_app.h"
#include "queue_family_indices.h"
#include "swap_chain_support_details.h"

namespace VulkanUtils {

struct PhysicalDevice {
    /**
     * @brief Choose a GPU to work with.
     * @param app The vulkan app.
     */
    static void PickPhysicalDevice(VulkanApp& app);

    /**
     * @brief Check if a given gpu is suitable for use.
     * @param device The gpu to check.
     * @param surface The surface.
     */
    static const bool IsDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface, const std::vector<const char*>& extensions);

    static const bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device, const std::vector<const char*>& extensions);
    
    /**
     * @brief Find all required queue families on specific gpu.
     * @param device The gpu.
     * @param surface The surface.
     */
    static QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
};

};