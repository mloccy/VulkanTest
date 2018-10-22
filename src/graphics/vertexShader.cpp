#include "vertexShader.h"

namespace Graphics
{
    VertexShader::VertexShader(const std::vector<char> & code, VkDevice device)
    {
        this->type = ShaderType::Vertex;
        this->shaderDevice = device;
        CreateShaderModule(code, device);
    }

    VkPipelineShaderStageCreateInfo VertexShader::GetShaderInfo()
    {
        VkPipelineShaderStageCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        info.module = shaderModule;
        info.pName = "main";
        return info;
    }

    VertexShader::VertexShader() {}
}