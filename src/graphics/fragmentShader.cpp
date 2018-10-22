#include "fragmentShader.h"

namespace Graphics
{
    FragmentShader::FragmentShader(const std::vector<char>& code, VkDevice device)
    {
        this->type = ShaderType::Fragment;
        this->shaderDevice = device;
        CreateShaderModule(code, device);
    }

    VkPipelineShaderStageCreateInfo FragmentShader::GetShaderInfo()
    {
        VkPipelineShaderStageCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        info.module = shaderModule;
        info.pName = "main";
        return info;
    }

    FragmentShader::FragmentShader() {}
}