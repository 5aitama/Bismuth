#include "semaphores.h"

using namespace VulkanUtils;

void Semaphores::Init(VulkanApp& app) {
    app.imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    app.renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);

    app.inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    app.imagesInFlight.resize(app.swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    };

    VkFenceCreateInfo fenceInfo {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT,
    };

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(app.device, &semaphoreInfo, nullptr, &app.imageAvailableSemaphores[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create imageAvailable semaphore !");
        }

        if (vkCreateSemaphore(app.device, &semaphoreInfo, nullptr, &app.renderFinishedSemaphores[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create renderFinished semaphore !");
        }

        if (vkCreateFence(app.device, &fenceInfo, nullptr, &app.inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create fence !");
        }
    }
}