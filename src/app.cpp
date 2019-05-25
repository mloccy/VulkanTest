#include "app.h"
#include "Input/keyboard.h"
#include "Input/mouse.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <sstream>

#if defined (_WIN64)

namespace fs = std::experimental::filesystem;

#else

namespace fs = std::filesystem;

#endif

uint32_t App::Run()
{
    init();
    loop();
    cleanup();

    return 0;
}

App::App(const uint32_t width, const uint32_t height, const char * title, const char * shaderDir)
{
    this->width = width; this->height = height; this->title = title; this->shaderDir = shaderDir;
}

void App::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    auto monitor = glfwGetPrimaryMonitor();

    auto mode = glfwGetVideoMode(monitor);

    this->window = glfwCreateWindow(width, height, this->title.c_str(), nullptr, nullptr);

    Graphics::ShaderList loadedShaders;

    for (const auto& p : fs::directory_iterator(this->shaderDir))
    {
        std::ostringstream pathStream;
        pathStream << p;

        std::ifstream file(pathStream.str(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw new std::runtime_error("Couldn't open file");
        }

        size_t size = file.tellg();

        file.seekg(0);

        std::vector<char> buffer;
        buffer.resize(size);

        file.read(buffer.data(), size);

        file.close();

        std::ostringstream filenameStream;

        filenameStream << fs::path(pathStream.str()).filename();

        auto filename = filenameStream.str();

        auto pos = filename.find('.');

        auto pos2 = filename.find('.', pos + 1);

        auto ext = filename.substr(pos + 1, filename.length() - pos2);

        std::string lower;
        std::locale loc;
        for (auto const c : ext)
        {
            lower += std::tolower(c, loc);
        }
        auto type = Graphics::Shader::StringToShaderType(lower);

        loadedShaders.push_back(std::make_tuple(filename, type, buffer));
    }

    graphicsBackend = Graphics::Vulkan::VulkanBackend::Make(window, loadedShaders);

    graphicsBackend->BeginInit(title);
    graphicsBackend->LoadProgram("test");

    const std::vector<glm::vec3> positions =
    {
        { -0.5, -0.5, 0.5 },
        { 0.5, -0.5, 0.5 },
        { -0.5,  0.5, 0.5 },
        { 0.5,  0.5, 0.5 },

        { -0.5,  0.5, -0.5 },
        { 0.5,  0.5, -0.5 },
        { -0.5, -0.5, -0.5 },
        { 0.5, -0.5, -0.5 }
    };

    const std::vector<glm::vec2> texCoords =
    {
        { 0.0, 1.0 },
        { 1.0, 1.0 },
        { 0.0, 0.0 },
        { 1.0, 0.0 },
    };

    const std::vector<std::vector<glm::vec2>> faces =
    {
        {{1, 1}, {2, 2}, {3, 3}},
        {{3, 3}, {2, 2}, {4, 4}},

        {{3, 1}, {4, 2}, {5, 3}},
        {{5, 3}, {4, 2}, {6, 4}},

        {{5, 4}, {6, 3}, {7, 2}},
        {{7, 2}, {6, 3}, {8, 1}},

        {{7, 1}, {8, 2}, {1, 3}},
        {{1, 3}, {8, 2}, {2, 4}},

        {{2, 1}, {8, 2}, {4, 3}},
        {{4, 3}, {8, 2}, {6, 4}},

        {{7, 1}, {1, 2}, {5, 3}},
        {{5, 3}, {1, 2}, {3, 4}}
    };

    std::vector<Graphics::Vertex> vertices;
    std::vector<uint32_t> indices;

    std::unordered_map<Graphics::Vertex, uint32_t> unique;

    for (const auto& face : faces)
    {
        for (const auto& faceVert : face)
        {
            Graphics::Vertex v0;

            v0.position = positions.at(faceVert.x - 1);
            v0.texcoord0 = texCoords.at(faceVert.y - 1);

            //v0.texcoord0.y = 1.0 - v0.texcoord0.y;
            //v0.texcoord0.x = 1.0 - v0.texcoord0.x;

            if (unique.count(v0) == 0)
            {
                unique[v0] = vertices.size();
                vertices.push_back(v0);
            }

            indices.push_back(unique[v0]);
        }
    }

    graphicsBackend->LoadTexture("texture.jpg");
    graphicsBackend->EndInit();
    graphicsBackend->LoadModel(vertices, indices);

    glfwSetKeyCallback(this->window, Input::Keyboard::HandleKey);
    glfwSetCursorPosCallback(this->window, Input::Mouse::HandleMouseMove);
    glfwSetMouseButtonCallback(this->window, Input::Mouse::HandleMouseClick);
}

void App::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        graphicsBackend->DrawFrame();
    }
}

void App::cleanup()
{
    glfwDestroyWindow(window);

    glfwTerminate();

    graphicsBackend->Cleanup();

    delete graphicsBackend;
}