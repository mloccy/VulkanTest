#include "app.h"

uint32_t App::Run()
{
    init();
    loop();
    cleanup();

    return 0;
}

App::App(const uint32_t width, const uint32_t height, const char * title)
{
    this->width = width; this->height = height; this->title = title;
}

void App::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
    graphicsBackend = Graphics::Vulkan::VulkanBackend::Make(window);

    graphicsBackend->Init(title);
}

void App::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

void App::cleanup()
{
    glfwDestroyWindow(window);

    glfwTerminate();

    graphicsBackend->Cleanup();

    delete graphicsBackend;
}