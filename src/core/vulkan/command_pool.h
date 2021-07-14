#pragma once

#include <vulkan/vulkan.h>
#include "vulkan_app.h"
#include "physical_device.h"

namespace VulkanUtils {

struct CommandPool {
    static void Init(VulkanApp& app);
};

};