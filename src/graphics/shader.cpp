#include "shader.h"

namespace Graphics
{
    ShaderType Shader::StringToShaderType(const std::string & str)
    {
        if (str.find("vs") != std::string::npos || str.find("vert") != std::string::npos)
        {
            return ShaderType::Vertex;
        }
        else if (str.find("fs") != std::string::npos || str.find("frag") != std::string::npos)
        {
            return ShaderType::Fragment;
        }
        else if (str.find("gs") != std::string::npos || str.find("geom") != std::string::npos)
        {
            return ShaderType::Geometry;
        }
        else if (str.find("tes") != std::string::npos || str.find("tese") != std::string::npos)
        {
            return ShaderType::TessellationEvaluation;
        }
        else if (str.find("tcs") != std::string::npos || str.find("tesc") != std::string::npos)
        {
            return ShaderType::TessellationControl;
        }

        throw new std::runtime_error("Invalid extension");
    }
    void Shader::CreateShaderModule(const std::vector<char>& code, VkDevice device)
    {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
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
        return shaderModule;
    }

    Shader::~Shader()
    {
        if (this->shaderDevice != nullptr && this->shaderModule != nullptr)
        {
            vkDestroyShaderModule(this->shaderDevice, this->shaderModule, nullptr);
        }
    }
}