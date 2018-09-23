#ifndef APP_H
#define APP_H

#include <stdint.h>
#include "graphics\graphics_backend.h"
#include "graphics\vulkan\vulkan_backend.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class App
{
public:
    uint32_t Run();
    App(uint32_t width, uint32_t height, const char * title);

private:

    uint32_t width;
    uint32_t height;
    const char * title;
    GLFWwindow * window;

    Graphics::GraphicsBackend * graphicsBackend;

    void init();

    void loop();

    void cleanup();
};
#endif // ! APP_H