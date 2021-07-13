#pragma once
#include <fstream>
#include <vector>
#include <vulkan/vulkan.h>

namespace VulkanUtils {

/**
 * @brief Create and manage shader easly.
 */
struct Shader {
    const VkDevice device       = VK_NULL_HANDLE;
    VkShaderModule shaderModule = VK_NULL_HANDLE;

    /**
     * @brief Create new shader instance.
     * 
     * @param path The compiled shader file path (.spv).
     * @param device The device.
     */
    Shader(const std::string& path, const VkDevice& device);
    ~Shader();

    /**
     * @brief Create a shader module.
     * 
     * @param bytecode The compiled shader data (.spv).
     * @param device The device.
     */
    VkShaderModule CreateShaderModule(const std::vector<char>& bytecode, const VkDevice& device);
};

};