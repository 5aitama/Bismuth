#pragma once

#include <vulkan/vulkan.h>
#include "vulkan_app.h"

namespace VulkanUtils {

struct CommandBuffers {
    static void Init(VulkanApp& app);
};

};