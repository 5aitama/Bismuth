#pragma once

#include <vulkan/vulkan.h>
#include "vulkan_app.h"

namespace VulkanUtils {

struct Semaphores {
    static void Init(VulkanApp& app);
};

};