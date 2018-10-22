#ifndef VERTEX_H
#define VERTEX_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "graphics_includes.h"
#include <array>

namespace Graphics
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 colour;
        glm::vec2 texcoord0;
        glm::vec2 texcoord1;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        bool operator==(const Vertex& other) const
        {
            return
                position == other.position &&
                colour == other.colour &&
                texcoord0 == other.texcoord0 &&
                texcoord1 == other.texcoord1 &&
                normal == other.normal &&
                tangent == other.tangent &&
                bitangent == other.bitangent;
        }

        static VkVertexInputBindingDescription getBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription = {};

            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 7> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 7> attributeDescriptions = {};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, position);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, colour);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texcoord0);

            attributeDescriptions[3].binding = 0;
            attributeDescriptions[3].location = 3;
            attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[3].offset = offsetof(Vertex, texcoord1);

            attributeDescriptions[4].binding = 0;
            attributeDescriptions[4].location = 4;
            attributeDescriptions[4].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[4].offset = offsetof(Vertex, normal);

            attributeDescriptions[5].binding = 0;
            attributeDescriptions[5].location = 5;
            attributeDescriptions[5].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[5].offset = offsetof(Vertex, tangent);

            attributeDescriptions[6].binding = 0;
            attributeDescriptions[6].location = 6;
            attributeDescriptions[6].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[6].offset = offsetof(Vertex, bitangent);

            return attributeDescriptions;
        }
    };
}

namespace std
{
    template<> struct hash<Graphics::Vertex>
    {
        size_t operator()(Graphics::Vertex const& vertex) const
        {
            return (
                (hash<glm::vec3>()(vertex.position) ^
                (hash<glm::vec3>()(vertex.colour) << 1)) >> 1) ^
                    (hash<glm::vec2>()(vertex.texcoord0) << 1) ^
                (hash<glm::vec2>()(vertex.texcoord1) << 1) ^
                (hash<glm::vec3>()(vertex.normal) << 1) ^
                (hash<glm::vec3>()(vertex.tangent) << 1) ^
                (hash<glm::vec3>()(vertex.bitangent) << 1);
        }
    };
}

#endif // !VERTEX_H
