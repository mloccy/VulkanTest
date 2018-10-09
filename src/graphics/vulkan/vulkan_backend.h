#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H
#include "../graphics_backend.h"
#include "../util/logging/logger.h"
#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

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
    };
}
#endif // !VULKAN_BACKEND_H
