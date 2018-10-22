#ifndef APP_H
#define APP_H
#include "graphics/vertex.h"
#include <stdint.h>
#include "graphics/graphics_backend.h"
#include "graphics/vulkan_backend.h"
#include "graphics/graphics_includes.h"

class App
{
public:
    uint32_t Run();
    App(uint32_t width, uint32_t height, const char * title, const char * shaderDir);

private:

    uint32_t width;
    uint32_t height;
    std::string title;
    std::string shaderDir;
    GLFWwindow * window;

    Graphics::GraphicsBackend * graphicsBackend;

    void init();

    void loop();

    void cleanup();
};
#endif // ! APP_H