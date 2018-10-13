#include "vertexShader.h"

namespace Graphics
{
    VertexShader::VertexShader(const std::string & code, VkDevice device)
    {
        this->type = ShaderType::Vertex;
        this->shaderDevice = device;
        CreateShaderModule(code, device);
    }

    VertexShader::VertexShader() {}
}