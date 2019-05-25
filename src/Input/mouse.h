#ifndef MOUSE_H
#define MOUSE_H

#include "../Graphics/graphics_includes.h"

namespace Input
{
    enum class MouseButton
    {
        LMB,
        MMB,
        RMB
    };

    class Mouse
    {
    public:
        static void HandleMouseMove(GLFWwindow * window, double x, double y);
        static void HandleMouseClick(GLFWwindow * window, int button, int action, int mods);

        static Mouse * GetInstance();

    private:
        Mouse()
        {
        }

        static Mouse * Instance;
    };
}

#endif // !MOUSE_H
