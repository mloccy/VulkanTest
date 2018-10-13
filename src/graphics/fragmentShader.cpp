#include "fragmentShader.h"

namespace Graphics
{
    FragmentShader::FragmentShader(const std::string& code, VkDevice device)
    {
        this->type = ShaderType::Fragment;
        this->shaderDevice = device;
        CreateShaderModule(code, device);
    }

    FragmentShader::FragmentShader() {}
}