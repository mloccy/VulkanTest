#ifndef PROJECTIONDATA
#define PROJECTIONDATA
#include "graphics_includes.h"
namespace Graphics
{
    struct ProjectionData
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };
}
#endif // !PROJECTIONDATA