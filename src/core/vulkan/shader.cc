#include "shader.h"

using namespace VulkanUtils;

Shader::Shader(const std::string& path, const VkDevice& device) : device(device) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(std::string {"Failed to open file \"" + path + "\"!"});
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    shaderModule = CreateShaderModule(buffer, device);
}

Shader::~Shader() {
    if (shaderModule != VK_NULL_HANDLE) {
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }
}

VkShaderModule Shader::CreateShaderModule(const std::vector<char>& bytecode, const VkDevice& device) {
    std::cout << bytecode.size() << std::endl;
    VkShaderModuleCreateInfo createInfo {
        .sType      = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize   = bytecode.size(),
        .pCode      = reinterpret_cast<const uint32_t*>(bytecode.data()),
    };

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module!");
    }

    return shaderModule;
}