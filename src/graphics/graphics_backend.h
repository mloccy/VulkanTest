#ifndef GRAPHICS_BACKEND_H
#define GRAPHICS_BACKEND_H

namespace Graphics
{
    class GraphicsBackend
    {
    public:
        virtual void Init(const char * title) = 0;
        virtual void Cleanup() = 0;
    };
}
#endif // !