#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "shader.h"

namespace Graphics
{
    class FragmentShader : public Shader
    {
    public:
        FragmentShader::FragmentShader(const std::vector<char>& code, VkDevice device);
        VkPipelineShaderStageCreateInfo GetShaderInfo();
        FragmentShader();
    };
}
#endif // !FRAGMENTSHADER_H
