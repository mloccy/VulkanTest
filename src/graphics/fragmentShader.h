#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "shader.h"

namespace Graphics
{
    class FragmentShader : public Shader
    {
    public:
        FragmentShader::FragmentShader(const std::string& code, VkDevice device);

        FragmentShader();
    };
}
#endif // !FRAGMENTSHADER_H
