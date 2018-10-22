#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "shader.h"

namespace Graphics
{
    class VertexShader : public Shader
    {
    public:
        VertexShader(const std::vector<char> & code, VkDevice device);
        VkPipelineShaderStageCreateInfo GetShaderInfo();
        VertexShader();
    };
}

#endif // !VERTEXSHADER_H
