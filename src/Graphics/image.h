#ifndef IMAGE_H
#define IMAGE_H
#include <stdint.h>
#include <string>

namespace Graphics
{
    class Image
    {
    private:
        uint8_t *data;
        Image() { data = nullptr; };

        uint32_t width;
        uint32_t height;
        uint8_t channels;

    public:

        uint32_t Width();
        uint32_t Height();
        uint8_t Channels();
        uint8_t * Data();
        uint64_t Size();

        static Image * Open(const std::string & path);
        ~Image();
    };
}

#endif // !IMAGE_H
