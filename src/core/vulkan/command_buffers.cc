#include "command_buffers.h"

using namespace VulkanUtils;

void CommandBuffers::Init(VulkanApp& app) {
    app.commandBuffers.resize(app.swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool        = app.commandPool,
        .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = (uint32_t) app.commandBuffers.size(),
    };

    if (vkAllocateCommandBuffers(app.device, &allocInfo, app.commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create command buffers !");
    }

    for (size_t i = 0; i < app.commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo {
            .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags              = 0,
            .pInheritanceInfo   = nullptr,
        };

        if (vkBeginCommandBuffer(app.commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed on begin registred command buffer !");
        }

        VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

        VkRenderPassBeginInfo renderPassInfo {
            .sType              = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .renderPass         = app.renderPass,
            .framebuffer        = app.swapChainFramebuffers[i],
            .renderArea.offset  = { 0, 0 },
            .renderArea.extent  = app.swapChainExtent,
            .clearValueCount    = 1,
            .pClearValues       = &clearColor,
        };

        vkCmdBeginRenderPass(app.commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(app.commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, app.graphicsPipeline);
        vkCmdDraw(app.commandBuffers[i], 3, 1, 0, 0);
        vkCmdEndRenderPass(app.commandBuffers[i]);

        if (vkEndCommandBuffer(app.commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }
}