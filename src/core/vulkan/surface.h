#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "vulkan_app.h"
#include "../window/window.h"

namespace VulkanUtils {

struct Surface {

    static void Init(VulkanApp& app, Window& window);

};

};