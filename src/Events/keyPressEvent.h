#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <chrono>

#include "keyEvent.h"
#include "../input/keyboard.h"

namespace Events
{
    class KeyPressEvent : public KeyEvent
    {
    public:
        ~KeyPressEvent()
        {
        }

        KeyPressEvent(Input::Key key)
        {
            this->Key = key;
        }

        Input::Key Key;
    };
}
#endif