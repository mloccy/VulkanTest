#include "keyboard.h"
#include "../events/keyPressEvent.h"
#include "../events/keyReleaseEvent.h"
#include "../events/keyHoldEvent.h"

#include "../events/eventsPump.h"
namespace Input
{
    Key GLFWKeyToKey(int key, int scanCode, int mods)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            return Key::W;

        case GLFW_KEY_S:
            return Key::S;

        case GLFW_KEY_A:
            return Key::A;

        case GLFW_KEY_D:
            return Key::D;

        default:
            return Key::None;
        }
    }

    void Keyboard::HandleKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Key pressedKey = GLFWKeyToKey(key, scancode, mods);

        Events::Event * evt;

        switch (action)
        {
        case GLFW_PRESS:
            evt = new Events::KeyPressEvent(pressedKey);
            break;

        case GLFW_RELEASE:
            evt = new Events::KeyReleaseEvent(pressedKey);
            break;

        case GLFW_REPEAT:
            evt = new Events::KeyHoldEvent(pressedKey);
            break;

        default:
            return;
        }

        if (pressedKey != Key::None)
        {
            Events::EventPump::FireEvent(evt);
        }
    }

    Keyboard* Keyboard::instance = 0;

    Keyboard::Keyboard()
    {
    }

    Keyboard * Keyboard::GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new Keyboard();
        }

        return instance;
    }

    void Keyboard::DestroyInstance()
    {
        delete instance;
    }
}