#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <set>

#include "vulkan_app.h"

namespace VulkanUtils {

struct LogicalDevice {
    static void Init(VulkanApp& app);
};

};