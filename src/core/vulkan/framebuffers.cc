#include "framebuffers.h"

using namespace VulkanUtils;

void Framebuffers::Init(VulkanApp& app) {
    app.swapChainFramebuffers.resize(app.swapChainImageViews.size());

    for (size_t i = 0; i < app.swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
            app.swapChainImageViews[i],
        };

        VkFramebufferCreateInfo framebufferInfo {
            .sType              = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass         = app.renderPass,
            .attachmentCount    = 1,
            .pAttachments       = attachments,
            .width              = app.swapChainExtent.width,
            .height             = app.swapChainExtent.height,
            .layers             = 1,
        };

        if (vkCreateFramebuffer(app.device, &framebufferInfo, nullptr, &app.swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create the framebuffer !");
        }
    }
}