#ifndef SHADER_H
#define SHADER_H

#include "graphics_includes.h"
#include <string>
#include <vector>
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
        static ShaderType StringToShaderType(const std::string & str);
        VkShaderModule GetShaderModule();
        ShaderType GetType();
        virtual VkPipelineShaderStageCreateInfo GetShaderInfo() = 0;
        virtual ~Shader();

    protected:
        ShaderType type;
        VkShaderModule shaderModule;
        VkDevice shaderDevice;
        void CreateShaderModule(const std::vector<char>& code, VkDevice device);
    };
}
#endif // !SHADER_H