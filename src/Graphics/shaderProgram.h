#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <algorithm>
#include <functional>

#include "graphics_includes.h"
#include "vertexShader.h"
#include "fragmentShader.h"

namespace Graphics
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& name, std::vector <std::pair<std::string, Shader *>> shaders);
        ShaderProgram();
        std::vector<VkPipelineShaderStageCreateInfo> GetProgramStageInfo();

    private:
        std::vector<Shader *> definedShaderModules;
    };
}
#endif // !SHADERPROGRAM_H