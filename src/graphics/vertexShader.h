#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "shader.h"

namespace Graphics
{
    class VertexShader : public Shader
    {
    public:
        VertexShader(const std::string & code, VkDevice device);
        VertexShader();
    };
}

#endif // !VERTEXSHADER_H
