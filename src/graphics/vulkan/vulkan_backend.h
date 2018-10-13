#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H
#include "../graphics_backend.h"
#include "../vertexShader.h"
#include "../fragmentShader.h"

#include "../util/logging/logger.h"
#include "../graphics_includes.h"

#include <string>
#include <vector>

namespace Graphics::Vulkan
{
    class VulkanBackend : public GraphicsBackend
    {
    public:
        void Init(const char * title);
        void Cleanup();
        static VulkanBackend * Make(GLFWwindow *window);
    private:
        Util::Logging::Logger logger;

        VulkanBackend();

        VulkanBackend(GLFWwindow * window);

        GLFWwindow * window;
        VkDebugUtilsMessengerEXT callback;
        VkInstance instance;
        VkPhysicalDevice phyDevice;
        VkDevice device;
        VkQueue queue;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        VertexShader vShader;
        FragmentShader fShader;
    };
}
#endif // !VULKAN_BACKEND_H
