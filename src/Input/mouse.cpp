#include "mouse.h"

#include "../Events/mouseButtonPressEvent.h"
#include "../Events/mouseButtonPressHoldEvent.h"
#include "../Events/mouseButtonReleaseEvent.h"
#include "../Events/mouseMoveEvent.h"

#include "../Events/eventsPump.h"

namespace Input
{
    Mouse * Mouse::Instance = nullptr;

    Mouse * Mouse::GetInstance()
    {
        if (Instance == nullptr)
        {
            Instance = new Mouse();
        }

        return Instance;
    }

    void Mouse::HandleMouseMove(GLFWwindow * window, double x, double y)
    {
        auto evt = new Events::MouseMoveEvent(x, y);

        Events::EventPump::FireEvent(evt);
    }

    void Mouse::HandleMouseClick(GLFWwindow * window, int button, int action, int mods)
    {
    }
}