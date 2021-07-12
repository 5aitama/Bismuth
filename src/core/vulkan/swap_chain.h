#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <algorithm>

#include "vulkan_app.h"
#include "swap_chain_support_details.h"

namespace VulkanUtils {

struct SwapChain {

    static void Init(VulkanApp& app);

    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};

};