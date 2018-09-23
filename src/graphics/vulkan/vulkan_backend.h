#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H
#include "../graphics_backend.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <vector>namespace Graphics::Vulkan

namespace Graphics::Vulkan
{
    class VulkanBackend : public GraphicsBackend
    {
    public:
        void Init(const char * title);
        void Cleanup();

    private:
        VkDebugUtilsMessengerEXT callback;
        VkInstance instance;
        void initInstance(const char * title);
    };
}
#endif // !VULKAN_BACKEND_H
