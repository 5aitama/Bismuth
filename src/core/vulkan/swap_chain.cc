#include "swap_chain.h"

using namespace VulkanUtils;

void SwapChain::Init(VulkanApp& app) {
    auto swapChainSupport = SwapChainSupportDetails::QuerySwapChainSupport(app.physicalDevice, app.surface);

    auto surfaceFormat  = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    auto presentMode    = ChooseSwapPresentMode(swapChainSupport.presentModes);
    auto extent         = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.maxImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    auto isSameFamily = app.indices.graphicsFamily == app.indices.presentFamily;
    
    uint32_t queueFamilyIndices[] = { 
        app.indices.graphicsFamily.value(), 
        app.indices.presentFamily.value() 
    };

    VkSwapchainCreateInfoKHR createInfo {
        .sType                  = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface                = app.surface,
        .minImageCount          = imageCount,
        .imageFormat            = surfaceFormat.format,
        .imageColorSpace        = surfaceFormat.colorSpace,
        .imageExtent            = extent,
        .imageArrayLayers       = 1,
        .imageUsage             = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode       = isSameFamily ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
        .queueFamilyIndexCount  = static_cast<uint32_t>(isSameFamily ? 0 : 2),
        .pQueueFamilyIndices    = isSameFamily ? nullptr : queueFamilyIndices,
        .preTransform           = swapChainSupport.capabilities.currentTransform,
        .compositeAlpha         = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode            = presentMode,
        .clipped                = VK_TRUE,
        .oldSwapchain           = VK_NULL_HANDLE,
    };

    if (vkCreateSwapchainKHR(app.device, &createInfo, nullptr, &app.swapChain) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create swap chain !");
    }

    vkGetSwapchainImagesKHR(app.device, app.swapChain, &imageCount, nullptr);
    app.swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(app.device, app.swapChain, &imageCount, app.swapChainImages.data());

    app.swapChainImageFormat    = surfaceFormat.format;
    app.swapChainExtent         = extent;

}

VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = { 800, 600 };
        actualExtent.width = 
            std::max(capabilities.minImageExtent.width, 
            std::min(capabilities.maxImageExtent.width,
            actualExtent.width));

        actualExtent.height = 
            std::max(capabilities.minImageExtent.height, 
            std::min(capabilities.maxImageExtent.height,
            actualExtent.height));

        return actualExtent;
    }
}