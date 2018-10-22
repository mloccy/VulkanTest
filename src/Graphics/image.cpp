#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Graphics
{
    Image * Image::Open(const std::string &path)
    {
        int x, y, c;

        auto img = new Image();

        img->data = stbi_load(path.c_str(), &x, &y, &c, 4);

        if (img->data == nullptr)
        {
            throw new std::runtime_error("Could not load image");
        }

        img->width = (uint32_t)x;
        img->height = (uint32_t)y;
        img->channels = 4;
        return img;
    }

    Image::~Image()
    {
        if (data != nullptr)
        {
            stbi_image_free(data);
        }
    }

    uint32_t Image::Width()
    {
        return width;
    }

    uint32_t Image::Height()
    {
        return height;
    }

    uint8_t Image::Channels()
    {
        return channels;
    }

    uint8_t * Image::Data()
    {
        return data;
    }

    uint64_t Image::Size()
    {
        return width * height * channels;
    }
}