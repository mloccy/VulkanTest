#ifndef VULKAN_BACKEND_H
#define VULKAN_BACKEND_H
#include "graphics_backend.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "shaderProgram.h"
#include "../Utils/logger.h"
#include "graphics_includes.h"
#include "vertex.h"
#include "projectionData.h"
#include "../Events/mouseEvent.h"
#include "../Events/mouseMoveEvent.h"
#include "../Events/mouseButtonPressEvent.h"
#include "../Events/mouseButtonPressHoldEvent.h"
#include "../Events/mouseButtonReleaseEvent.h"

#include "../Events//keyEvent.h"
#include "../events/keyPressEvent.h"
#include "../events/keyReleaseEvent.h"
#include "../events/keyHoldEvent.h"

#include "image.h"
#include <string>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Graphics::Vulkan
{
    class VulkanBackend : public GraphicsBackend
    {
    public:
        void BeginInit(const std::string& title);
        void EndInit();
        void Cleanup();
        void DrawFrame();
        void LoadProgram(const std::string & name);
        void LoadModel(const std::vector<Vertex> & modelData, const std::vector<uint32_t> & indices);
        void HandleEvent(Events::Event * evt);

        static VulkanBackend * Make(GLFWwindow *window, ShaderList shaderList);
    private:

        Util::Logging::Logger logger;

        VulkanBackend();

        VulkanBackend(GLFWwindow * window, ShaderList loadedShaders);

        void HandleMouseEvent(Events::MouseEvent * evt);
        void HandleKeyEvent(Events::KeyEvent * evt);

        void LoadTexture(const std::string & path);
        void CreateSurface(GLFWwindow  *window, VkInstance instance);
        void CreateInstance(const std::string& title);
        void SetupDebugCallback(VkDebugUtilsMessengerEXT * callback);
        void SelectPhysicalDevice();
        void RecordRender();
        void SetupTransientOpsQueue();
        void RecreateSwapChains();
        void CreateSwapChain(bool reuse);
        void CreateImageViews();
        void CreateRenderPass();
        void CreatePresentCommandPool();
        void CreateDescriptorSetLayout();
        void CreateDescriptorPool();
        void CreateGraphicsPipeline();
        void CleanupSwapchain();
        void CreateLogicalDevice();
        void UpdateUniformData(uint32_t index);
        void CreateDescriptorSets();
        void CreateDepthResources();
        void CreateShaders();
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void CopyBuffer(
            VkBuffer srcBuffer,
            VkBuffer dstBuffer,
            VkDevice device,
            VkQueue queue,
            VkCommandPool pool,
            VkDeviceSize size);
        void CreateImage(
            uint32_t width,
            uint32_t height,
            VkFormat format,
            VkImageTiling tiling,
            VkImageUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkImage& image,
            VkDeviceMemory& imageMemory);

        VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void CreateTextureSampler();
        VkCommandBuffer BeginSingleTimeCommands(VkCommandPool pool);
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

        VkImage textureImage;
        VkImageView textureImageView;
        VkSampler textureSampler;

        VkDeviceMemory textureImageMemory;

        GLFWwindow * window;
        VkDebugUtilsMessengerEXT callback;
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        VkQueue presentQueue;
        VkQueue transferQueue;

        uint32_t  queueIndicies[2];

        VkSurfaceFormatKHR swapChainFormat;
        VkSurfaceKHR surface;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        ShaderList loadedShaders;
        std::vector<std::pair<std::string, Shader *>> shaderModules;

        ShaderProgram currentProgram;
        std::vector<Vertex> currentModelVertices;
        std::vector<uint32_t> currentModelIndices;
        VkViewport viewport;
        VkRect2D scissor;
        VkDescriptorSetLayout descriptorSetLayout;

        VkPipelineLayout pipelineLayout;

        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;

        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkCommandPool presentCommandPool;
        VkCommandPool transientCommandPool;
        VkDescriptorPool descriptorPool;

        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        VkSurfaceCapabilitiesKHR caps;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        ProjectionData camera;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 right;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        float verticalAngle = 0.0f;
        float horizontalAngle = 0.0f;
        float initialFOV = 45.0f;
        float moveSpeed = 0.25f;
        float mouseSpeed = 0.005f;

        size_t currentFrame = 0;
        const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
    };
}
#endif // !VULKAN_BACKEND_H
