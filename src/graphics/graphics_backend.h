#ifndef GRAPHICS_BACKEND_H
#define GRAPHICS_BACKEND_H
#include <string>
#include <tuple>
#include <vector>
#include "shader.h"
#include "vertex.h"
#include "../events/iEventHandler.h"
#include "../events/eventsPump.h"

namespace Graphics
{
    typedef std::vector<std::tuple<std::string, ShaderType, std::vector<char>>> ShaderList;

    class GraphicsBackend : public Events::IEventHandler
    {
    public:
        virtual void BeginInit(const std::string & title) = 0;
        virtual void EndInit() = 0;
        virtual void Cleanup() = 0;
        virtual void DrawFrame() = 0;
        virtual void LoadProgram(const std::string & name) = 0;
        virtual void LoadModel(const std::vector<Vertex> & modelData, const std::vector<uint32_t> & indices) = 0;
        virtual void LoadTexture(const std::string & path) = 0;

        GraphicsBackend()
        {
            Events::EventPump::RegisterHandler(this);
        }
    };
}
#endif // !