#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <chrono>

#include "event.h"
#include "../input/keyboard.h"

namespace Events
{
    class KeyPressEvent : public Event
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