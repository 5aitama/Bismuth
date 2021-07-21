#include "shader.h"

using namespace Bismuth;

Shader::Shader(const char* vert, const char* frag, const VkDevice& device) : device(device) {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    // options.SetOptimizationLevel(shaderc_optimization_level::shaderc_optimization_level_performance);
    
    auto vShaderFile = std::ifstream(vert, std::ios::in);
    
    if (!vShaderFile.is_open()) {
        throw std::runtime_error(std::string("Failed to open vertex shader \"") + vert + '"');
    }
    
    auto vBuffer = ReadShaderFile(vShaderFile);
    auto vStatus = compiler.CompileGlslToSpv(vBuffer.data(), vBuffer.size(), shaderc_glsl_vertex_shader, vert, options);

    if (vStatus.GetCompilationStatus() != shaderc_compilation_status_success) {
        throw std::runtime_error("Faile to compile vertex shader");
    }

    auto fShaderFile = std::ifstream(frag, std::ios::in);

    if (!fShaderFile.is_open()) {
        throw std::runtime_error(std::string("Failed to open fragment shader \"") + frag + '"');
    }

    auto fBuffer = ReadShaderFile(fShaderFile);
    auto fStatus = compiler.CompileGlslToSpv(fBuffer.data(), fBuffer.size(), shaderc_glsl_fragment_shader, frag, options);
    
    if (fStatus.GetCompilationStatus() != shaderc_compilation_status_success) {
        throw std::runtime_error("Faile to compile fragment shader");
    }

    vSpirv = std::vector<uint32_t>(vStatus.begin(), vStatus.end());
    fSpirv = std::vector<uint32_t>(fStatus.begin(), fStatus.end());

    CreateVertexModule(device);
    CreateFragmentModule(device);
}

Shader::~Shader() {
    if (fShaderModule != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, fShaderModule, nullptr);

    if (vShaderModule != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, vShaderModule, nullptr);
}

const VkShaderModule& Shader::GetVertexShaderModule() const {
    return vShaderModule;
}

const VkShaderModule& Shader::GetFragmentShaderModule() const {
    return fShaderModule;
}

const std::vector<char> Shader::ReadShaderFile(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(length);
    file.read(buffer.data(), length);
    file.close();

    return buffer;
}

void Shader::CreateVertexModule(const VkDevice& device) {
    VkShaderModuleCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize   = vSpirv.size() * 4,
        .pCode      = vSpirv.data(),
    };

    if (vkCreateShaderModule(device, &createInfo, nullptr, &vShaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create the vertex shader module !");
    }
}

void Shader::CreateFragmentModule(const VkDevice& device) {
    VkShaderModuleCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize   = fSpirv.size() * 4,
        .pCode      = fSpirv.data(),
    };

    if (vkCreateShaderModule(device, &createInfo, nullptr, &fShaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create the fragment shader module !");
    }
}