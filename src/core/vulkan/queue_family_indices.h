#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

namespace VulkanUtils {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    
    const bool IsComplete();
};

};