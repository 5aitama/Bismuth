#pragma once

#include <vulkan/vulkan.h>
#include "vulkan_app.h"
#include "shader.h"
#include "../shader.h"

namespace VulkanUtils {

struct GraphicsPipeline {
    static void Init(VulkanApp& app);
};

};