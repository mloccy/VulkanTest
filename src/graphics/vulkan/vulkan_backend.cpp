#include "vulkan_backend.h"
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

#include <vulkan\vulkan.h>

namespace Graphics::Vulkan
{
#ifdef NDEBUG
    bool enableValidationLayers = false;
#else
    bool enableValidationLayers = true;
#endif // NDEBUG

    const std::vector<const char*> validationLayers =
    {
        "VK_LAYER_LUNARG_standard_validation"
    };

    const std::vector<const char*> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    bool checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers)
        {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        Util::Logging::Logger * logger = (Util::Logging::Logger *)pUserData;

        std::string msg = pCallbackData->pMessage;

        msg += "\n";
        logger->Trace(msg.c_str());
        //std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, callback, pAllocator);
        }
    }

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const
        VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pCallback)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pCallback);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void setupDebugCallback(VkInstance instance, Util::Logging::Logger * logger, VkDebugUtilsMessengerEXT * callback)
    {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};

        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

        createInfo.pfnUserCallback = debugCallback;

        createInfo.pUserData = logger;

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, callback) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to set up debug callback!");
        }
    }

    VkInstance createInstance(const char * title)
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = title;
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.pEngineName = "";
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkInstance instance;
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }

        return instance;
    }

    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);

            if (requiredExtensions.empty())
            {
                break;
            }
        }

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
            && deviceFeatures.geometryShader
            && requiredExtensions.empty();
    }

    VkPhysicalDevice selectPhysicalDevice(VkInstance instance)
    {
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        int a = 2;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0)
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (auto device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw new std::runtime_error("No suitable device found");
        }

        return physicalDevice;
    }

    std::pair<VkQueue, VkDevice> createLogicalDevice(VkPhysicalDevice phyDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR * caps)
    {
        uint32_t nQueues;

        vkGetPhysicalDeviceQueueFamilyProperties(phyDevice, &nQueues, nullptr);

        std::vector<VkQueueFamilyProperties> queueProperties(nQueues);

        vkGetPhysicalDeviceQueueFamilyProperties(phyDevice, &nQueues, queueProperties.data());

        int i = 0;

        std::map<uint32_t, std::pair<uint32_t, VkQueueFamilyProperties>> scoresToQueues;
        for (auto queue : queueProperties)
        {
            if (queue.queueFlags & VK_QUEUE_GRAPHICS_BIT || queue.queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                VkBool32 supported;

                vkGetPhysicalDeviceSurfaceSupportKHR(phyDevice, i, surface, &supported);
                if (supported)
                {
                    uint32_t formatCount;
                    vkGetPhysicalDeviceSurfaceFormatsKHR(phyDevice, surface, &formatCount, nullptr);

                    std::vector<VkSurfaceFormatKHR> formats(formatCount);
                    vkGetPhysicalDeviceSurfaceFormatsKHR(phyDevice, surface, &formatCount, formats.data());

                    uint32_t modeCount;
                    vkGetPhysicalDeviceSurfacePresentModesKHR(phyDevice, surface, &modeCount, nullptr);

                    std::vector<VkPresentModeKHR> presentModes(modeCount);

                    vkGetPhysicalDeviceSurfacePresentModesKHR(phyDevice, surface, &modeCount, presentModes.data());

                    scoresToQueues[i] = std::make_pair(formats.size() * 10 + presentModes.size() * 2, queue);

                    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phyDevice, surface, caps);
                }
            }

            i++;
        }

        auto best = std::max_element(scoresToQueues.begin(), scoresToQueues.end(), [](
            const std::pair<uint32_t, std::pair<uint32_t, VkQueueFamilyProperties>>& p1,
            const std::pair<uint32_t, std::pair<uint32_t, VkQueueFamilyProperties>>& p2)
        {
            return p1.second.first < p2.second.first;
        });

        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = best->first;
        queueCreateInfo.queueCount = 1;

        float priority = 1.0f;
        queueCreateInfo.pQueuePriorities = &priority;

        VkPhysicalDeviceFeatures deviceFeatures = {};

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkDevice device;
        if (vkCreateDevice(phyDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }

        VkQueue queue;

        vkGetDeviceQueue(device, best->first, 0, &queue);

        return std::make_pair(queue, device);
    }

    VkSurfaceKHR createSurface(GLFWwindow  *window, VkInstance instance)
    {
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = glfwGetWin32Window(window);
        createInfo.hinstance = GetModuleHandle(nullptr);

        auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");

        VkSurfaceKHR surface;
        if (!CreateWin32SurfaceKHR || CreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface!");
        }

        return surface;
    }

    VkSwapchainKHR createSwapChain(
        VkInstance instance,
        VkDevice device,
        VkSurfaceKHR surface,
        VkPresentModeKHR presentMode,
        VkSurfaceCapabilitiesKHR caps,
        VkSurfaceFormatKHR surfaceFormat,
        std::vector<VkImage> & swapChainImages)
    {
        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;
        createInfo.minImageCount = caps.minImageCount + 1;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = caps.currentExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        createInfo.presentMode = presentMode;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.pNext = NULL;

        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = NULL;

        createInfo.preTransform = caps.currentTransform;

        createInfo.clipped = VK_TRUE;

        VkSwapchainKHR swapChain;

        if (vkCreateSwapchainKHR(device, &createInfo, NULL, &swapChain) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create swap chain!");
        }

        uint32_t nSwapChainImages;
        vkGetSwapchainImagesKHR(device, swapChain, &nSwapChainImages, NULL);

        swapChainImages.resize(nSwapChainImages);

        vkGetSwapchainImagesKHR(device, swapChain, &nSwapChainImages, swapChainImages.data());

        return swapChain;
    }

    std::vector<VkImageView> createImageViews(VkDevice device, std::vector<VkImage> swapChainImages, VkFormat swapChainFormat)
    {
        std::vector<VkImageView> views(swapChainImages.size());

        for (int i = 0; i < swapChainImages.size(); i++)
        {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(device, &createInfo, nullptr, &views[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create image views!");
            }
        }
        return views;
    }

    void createShaders(VkDevice device, VertexShader * vShader, FragmentShader * fShader)
    {
        *vShader = VertexShader(
            "#version 450 \
            #extension GL_ARB_separate_shader_objects : enable \
            out gl_PerVertex \
            { \
                vec4 gl_Position; \
            }; \
               \
            vec2 positions[3] = vec2[] \
            ( \
                vec2(0.0, -0.5), \
                vec2(0.5, 0.5), \
                vec2(-0.5, 0.5) \
            ); \
               \
            void main()\
            { \
                gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);\
            }", device);

        *fShader = FragmentShader("#version 450\
                                         #extension GL_ARB_separate_shader_objects : enable\
                                                                                           \
                                         layout(location = 0) out vec4 outColor;\
                                         void main() \
                                         {\
                                           outColor = vec4(1.0, 0.0, 0.0, 1.0);\
                                         }", device);
    }

    // Initialize vulkan display
    void VulkanBackend::Init(const char * title)
    {
        logger.Info("Initializing Vulkan backend...\n");
        instance = createInstance(title);

        setupDebugCallback(instance, &logger, &callback);
        surface = createSurface(window, instance);

        phyDevice = selectPhysicalDevice(instance);

        uint32_t imageCount;
        VkSurfaceCapabilitiesKHR caps;
        auto queueAndDevice = createLogicalDevice(phyDevice, surface, &caps);

        queue = queueAndDevice.first;
        device = queueAndDevice.second;

        imageCount = caps.minImageCount + 1;

        if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount)
        {
            imageCount = caps.maxImageCount;
        }

        VkSurfaceFormatKHR swapChainFormat = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

        swapChain = createSwapChain(
            instance,
            device,
            surface,
            VK_PRESENT_MODE_MAILBOX_KHR,
            caps,
            swapChainFormat,
            swapChainImages);

        swapChainImageViews = createImageViews(device, swapChainImages, swapChainFormat.format);

        createShaders(device, &this->vShader, &this->fShader);
    }

    void VulkanBackend::Cleanup()
    {
        for (auto view : swapChainImageViews)
        {
            vkDestroyImageView(device, view, nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyDevice(device, nullptr);

        DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);

        vkDestroyInstance(instance, nullptr);

        logger.Info("backend cleaned up...\n");
    }

    VulkanBackend *  VulkanBackend::Make(GLFWwindow * window)
    {
        return new VulkanBackend(window);
    }

    VulkanBackend::VulkanBackend(GLFWwindow * window) : window(window), logger("debug.log", Util::Logging::LogLevel::Trace, true) {}
}