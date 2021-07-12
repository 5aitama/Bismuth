#include "logical_device.h"

using namespace VulkanUtils;

void LogicalDevice::Init(VulkanApp& app) {

    float queuePriority = 1.0f;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    std::set<uint32_t> uniqueQueueFamilies = {
        app.indices.graphicsFamily.value(),
        app.indices.presentFamily.value(),
    };

    for (auto queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo {
            .sType              = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex   = queueFamily,
            .queueCount         = 1,
            .pQueuePriorities   = &queuePriority,
        };

        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures {};

    VkDeviceCreateInfo createInfo {
        .sType                      = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount       = static_cast<uint32_t>(queueCreateInfos.size()),
        .pQueueCreateInfos          = queueCreateInfos.data(),
    	
        #ifndef NDEBUG
        .enabledLayerCount          = static_cast<uint32_t>(app.instanceLayer.size()),
        .ppEnabledLayerNames        = app.instanceLayer.data(),
        #else
        .enabledLayerCount          = 0,
        .ppEnabledLayerNames        = nullptr,
        #endif

        .enabledExtensionCount      = static_cast<uint32_t>(app.deviceExtensions.size()),
        .ppEnabledExtensionNames    = app.deviceExtensions.data(),

        .pEnabledFeatures           = &deviceFeatures,
    };

    if (vkCreateDevice(app.physicalDevice, &createInfo, nullptr, &app.device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device !");
    }

    vkGetDeviceQueue(app.device, app.indices.graphicsFamily.value(), 0, &app.graphicsQueue);
    vkGetDeviceQueue(app.device, app.indices.presentFamily.value(), 0, &app.presentQueue);
}