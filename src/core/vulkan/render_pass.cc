#include "render_pass.h"

using namespace VulkanUtils;

void RenderPass::Init(VulkanApp& app) {
    VkAttachmentDescription colorAttachment {
        .format         = app.swapChainImageFormat,
        .samples        = VK_SAMPLE_COUNT_1_BIT,
        .loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    VkAttachmentReference colorAttachmentRef {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    };

    VkSubpassDescription subpass {
        .pipelineBindPoint      = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount   = 1,
        .pColorAttachments      = &colorAttachmentRef,
    };

    VkSubpassDependency dependency {
        .srcSubpass     = VK_SUBPASS_EXTERNAL,
        .dstSubpass     = 0,
        .srcStageMask   = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask  = 0,
        .dstStageMask   = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstAccessMask  = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
    };

    VkRenderPassCreateInfo renderPassInfo {
        .sType              = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount    = 1,
        .pAttachments       = &colorAttachment,
        .subpassCount       = 1,
        .pSubpasses         = &subpass,
        .dependencyCount    = 1,
        .pDependencies      = &dependency,
    };

    if (vkCreateRenderPass(app.device, &renderPassInfo, nullptr, &app.renderPass) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create render pass !");
    }
}