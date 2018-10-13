#include "shader.h"

namespace Graphics
{
    void Shader::CreateShaderModule(const std::string& code, VkDevice device)
    {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shader) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create shader module!");
        }
    }

    ShaderType Shader::GetType()
    {
        return type;
    }

    VkShaderModule Shader::GetShaderModule()
    {
        return shader;
    }

    Shader::~Shader()
    {
        if (this->shaderDevice != nullptr && this->shader != nullptr)
        {
            vkDestroyShaderModule(this->shaderDevice, this->shader, nullptr);
        }
    }
}