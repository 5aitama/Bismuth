#include "graphics_pipeline.h"

using namespace VulkanUtils;

void GraphicsPipeline::Init(VulkanApp& app) {
    auto shader = Bismuth::Shader(
        "../src/shaders/triangle/triangle.vert", 
		"../src/shaders/triangle/triangle.frag", 
        app.device
    );

    VkPipelineShaderStageCreateInfo vertShaderStageInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage                  = VK_SHADER_STAGE_VERTEX_BIT,
        .module                 = shader.GetVertexShaderModule(),
        .pName                  = "main",
        .pSpecializationInfo    = nullptr,
    };

    VkPipelineShaderStageCreateInfo fragShaderStageInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage                  = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module                 = shader.GetFragmentShaderModule(),
        .pName                  = "main",
        .pSpecializationInfo    = nullptr,
    };

    VkPipelineShaderStageCreateInfo shaderStages[] = { 
        vertShaderStageInfo, 
        fragShaderStageInfo,
    };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo {
        .sType                              = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount      = 0,
        .pVertexBindingDescriptions         = nullptr,
        .vertexAttributeDescriptionCount    = 0,
        .pVertexAttributeDescriptions       = nullptr,
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssembly {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };

    VkViewport viewport {
        .x          = 0.0f,
        .y          = 0.0f,
        .width      = (float) app.swapChainExtent.width,
        .height     = (float) app.swapChainExtent.height,
        .minDepth   = 0.0f,
        .maxDepth   = 1.0f,
    };

    VkRect2D scissor {
        .offset = { 0, 0 },
        .extent = app.swapChainExtent,
    };

    VkPipelineViewportStateCreateInfo viewportState {
        .sType          = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount  = 1,
        .pViewports     = &viewport,
        .scissorCount   = 1,
        .pScissors      = &scissor,
    };

    VkPipelineRasterizationStateCreateInfo rasterizer {
        .sType                      = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable           = VK_FALSE,
        .rasterizerDiscardEnable    = VK_FALSE,
        .polygonMode                = VK_POLYGON_MODE_FILL,
        .lineWidth                  = 1.0f,
        .cullMode                   = VK_CULL_MODE_BACK_BIT,
        .frontFace                  = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable            = VK_FALSE,
        .depthBiasConstantFactor    = 0.0f,
        .depthBiasClamp             = 0.0f,
        .depthBiasSlopeFactor       = 0.0f,
    };

    VkPipelineMultisampleStateCreateInfo multisampling {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .sampleShadingEnable    = VK_FALSE,
        .rasterizationSamples   = VK_SAMPLE_COUNT_1_BIT,
        .minSampleShading       = 1.0f,
        .pSampleMask            = nullptr,
        .alphaToCoverageEnable  = VK_FALSE,
        .alphaToOneEnable       = VK_FALSE,
    };

    VkPipelineColorBlendAttachmentState colorBlendAttachment {
        .colorWriteMask         = VK_COLOR_COMPONENT_R_BIT | 
                                  VK_COLOR_COMPONENT_G_BIT | 
                                  VK_COLOR_COMPONENT_B_BIT | 
                                  VK_COLOR_COMPONENT_A_BIT,
        .blendEnable            = VK_TRUE,
        .srcColorBlendFactor    = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor    = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp           = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor    = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor    = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp           = VK_BLEND_OP_ADD,
    };

    VkPipelineColorBlendStateCreateInfo colorBlending {
        .sType              = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable      = VK_FALSE,
        .logicOp            = VK_LOGIC_OP_COPY,
        .attachmentCount    = 1,
        .pAttachments       = &colorBlendAttachment,
        .blendConstants[0] = 0.0f,
        .blendConstants[1] = 0.0f,
        .blendConstants[2] = 0.0f,
        .blendConstants[3] = 0.0f,
    };

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH,
    };

    VkPipelineDynamicStateCreateInfo dynamicState {
        .sType              = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount  = 2,
        .pDynamicStates     = dynamicStates,
    };
    
    VkPipelineLayoutCreateInfo pipelineLayoutInfo {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount         = 0,
        .pSetLayouts            = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges    = nullptr,
    };

    if (vkCreatePipelineLayout(app.device, &pipelineLayoutInfo, nullptr, &app.pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create the pipeline layout !");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo {
        .sType                  = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount             = 2,
        .pStages                = shaderStages,
        .pVertexInputState      = &vertexInputInfo,
        .pInputAssemblyState    = &inputAssembly,
        .pViewportState         = &viewportState,
        .pRasterizationState    = &rasterizer,
        .pMultisampleState      = &multisampling,
        .pDepthStencilState     = nullptr,
        .pColorBlendState       = &colorBlending,
        .pDynamicState          = nullptr,
        .layout                 = app.pipelineLayout,
        .renderPass             = app.renderPass,
        .subpass                = 0,
        .basePipelineHandle     = VK_NULL_HANDLE,
        .basePipelineIndex      = -1,
    };

    if (vkCreateGraphicsPipelines(app.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &app.graphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create the graphics pipeline !");
    }
}