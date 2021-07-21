#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.hpp>

namespace Bismuth {

struct Shader {
    /**
     * Create new shader.
     * 
     * @param vert The vertex shader path.
     * @param frag The fragment shader path.
     * @param device The vulkan device.
     */
    Shader(const char* vert, const char* frag, const VkDevice& device);
    ~Shader();

    const VkShaderModule& GetVertexShaderModule() const;
    const VkShaderModule& GetFragmentShaderModule() const;

    private:
    /**
     * Read shader file content.
     * 
     * @param file The shader file stream.
     * @return The shader file content.
     */
    const std::vector<char> ReadShaderFile(std::ifstream& file);

    /**
     * Create a vulkan shader module from the vertex shader.
     * @param device The vulkan device.
     * @return The vertex shader module.
     */
    void CreateVertexModule(const VkDevice& device);

    /**
     * Create a vulkan shader module from the fragment shader.
     * @param device The vulkan device.
     * @return The fragment shader module.
     */
    void CreateFragmentModule(const VkDevice& device);

    /** The glsl compiled to spir-v binaries of the vertex shader */
    std::vector<uint32_t> vSpirv;

    /** The glsl compiled to spir-v binaries of the fragment shader */
    std::vector<uint32_t> fSpirv;

    /** The vulkan vertex shader module */
    VkShaderModule vShaderModule = VK_NULL_HANDLE;

    /** The vulkan fragment shader module */
    VkShaderModule fShaderModule = VK_NULL_HANDLE;
    
    /** The vulkan device */
    const VkDevice& device;
};

}