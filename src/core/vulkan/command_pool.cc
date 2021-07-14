#include "command_pool.h"

using namespace VulkanUtils;

void CommandPool::Init(VulkanApp& app) {
    auto queueFamilyIndices = PhysicalDevice::FindQueueFamilies(app.physicalDevice, app.surface);

    VkCommandPoolCreateInfo poolInfo {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex   = queueFamilyIndices.graphicsFamily.value(),
        .flags              = 0,
    };

    if (vkCreateCommandPool(app.device, &poolInfo, nullptr, &app.commandPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create command pool !");
    }
}