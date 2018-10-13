#ifndef SHADER_H
#define SHADER_H

#include "graphics_includes.h"
#include <string>

namespace Graphics
{
    enum class ShaderType
    {
        Vertex,
        TessellationControl,
        TessellationEvaluation,
        Geometry,
        Fragment
    };
    class Shader
    {
    public:
        VkShaderModule GetShaderModule();
        ShaderType GetType();
        virtual ~Shader();

    protected:
        ShaderType type;
        VkShaderModule shader;
        VkDevice shaderDevice;
        void CreateShaderModule(const std::string& code, VkDevice device);
    };
}
#endif // !SHADER_H