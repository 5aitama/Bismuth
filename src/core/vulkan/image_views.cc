#include "image_views.h"

using namespace VulkanUtils;

void ImageViews::Init(VulkanApp& app) {
    app.swapChainImageViews.resize(app.swapChainImages.size());

    for (size_t i = 0; i < app.swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image      = app.swapChainImages[i],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = app.swapChainImageFormat,

            .components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.a = VK_COMPONENT_SWIZZLE_IDENTITY,

            .subresourceRange.aspectMask        = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.baseMipLevel      = 0,
            .subresourceRange.levelCount        = 1,
            .subresourceRange.baseArrayLayer    = 0,
            .subresourceRange.layerCount        = 1,
        };

        if (vkCreateImageView(app.device, &createInfo, nullptr, &app.swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image view!");
        }
    }
}