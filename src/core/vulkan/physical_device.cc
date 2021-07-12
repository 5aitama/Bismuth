#include "physical_device.h"

using namespace VulkanUtils;

void PhysicalDevice::PickPhysicalDevice(VulkanApp& app) {
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(app.instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("There is no gpu that support vulkan !");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(app.instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (IsDeviceSuitable(device, app.surface, app.deviceExtensions)) {
            app.physicalDevice = device;
            app.indices = FindQueueFamilies(device, app.surface);
            break;
        }
    }

    if (app.physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("There is no suitable gpu for this app !");
    }

    #ifndef NDEBUG
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(app.physicalDevice, &properties);

    std::cout << "Selected gpu name : \033[1;34m" << properties.deviceName << "\033[0m" << std::endl;
    #endif
}

const bool PhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface, const std::vector<const char*>& extensions) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    auto indices = FindQueueFamilies(device, surface);
    auto extensionsSupported = CheckDeviceExtensionSupport(device, extensions);
    auto swapChainAdequate = false;

    if (extensionsSupported) {
        auto swapChainSupport = SwapChainSupportDetails::QuerySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && indices.IsComplete() && extensionsSupported && swapChainAdequate;
}

const bool PhysicalDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& device, const std::vector<const char*>& extensions) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	for (const auto& extension : extensions) {
		auto found = false;

		for (const auto& availableExtension : availableExtensions) {
			if (strcmp(extension, availableExtension.extensionName) == 0) {
				found = true;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;
}

QueueFamilyIndices PhysicalDevice::FindQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
}