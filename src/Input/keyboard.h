#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../graphics/graphics_includes.h"
#include <string>
namespace Input
{
    enum class Key
    {
        W,
        A,
        S,
        D,
        None
    };
    class Keyboard
    {
    public:

        static void HandleKey(GLFWwindow* window, int key, int scancode, int action, int mods);
        static Keyboard * GetInstance();
        static void DestroyInstance();

        static std::string KeyToString(Key key)
        {
            switch (key)
            {
            case Key::A:
                return "A";

            case Key::D:
                return "D";

            case Key::S:
                return "S";

            case Key::W:
                return "w";

            case Key::None:
            default:
                return "";
            }
        }
    private:
        Keyboard();
        static Keyboard * instance;
    };
}

#endif // !1