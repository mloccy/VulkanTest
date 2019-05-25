#include "shaderProgram.h"

namespace Graphics
{
    ShaderProgram::ShaderProgram()
    {
    }

    template <typename T>
    class CompareFunc
    {
    public:

        std::function<bool(std::pair<std::string, Shader *>)> Comparer;

        CompareFunc(const std::string &name)
        {
            this->name = name;

            Comparer = [&](std::pair<std::string, Shader *>  A)
            {
                return dynamic_cast<T>(A.second) != nullptr && A.first == name;
            };
        }

    private:
        std::string name;
    };

    ShaderProgram::ShaderProgram(
        const std::string& name,
        std::vector <std::pair<std::string, Shader *>> shaders)
    {
        auto fCmp = CompareFunc<FragmentShader *>(name);
        auto vCmp = CompareFunc<VertexShader *>(name);

        auto fShaderPtr = std::find_if(shaders.begin(), shaders.end(), fCmp.Comparer);

        auto vShaderPtr = std::find_if(shaders.begin(), shaders.end(), vCmp.Comparer);

        VertexShader * vShader = nullptr;
        FragmentShader * fShader = nullptr;

        if (vShaderPtr != shaders.end())
        {
            vShader = dynamic_cast<VertexShader*>((*vShaderPtr).second);
        }

        if (fShaderPtr != shaders.end())
        {
            fShader = dynamic_cast<FragmentShader*>((*fShaderPtr).second);
        }
        if (vShader != nullptr)
        {
            definedShaderModules.push_back(vShader);
        }

        if (fShader != nullptr)
        {
            definedShaderModules.push_back(fShader);
        }
    }

    std::vector<VkPipelineShaderStageCreateInfo> ShaderProgram::GetProgramStageInfo()
    {
        std::vector<VkPipelineShaderStageCreateInfo> shaderInfo;

        for (const auto& module : definedShaderModules)
        {
            shaderInfo.push_back(module->GetShaderInfo());
        }

        return shaderInfo;
    }
}