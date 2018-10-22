#ifndef KEYRELEASEEVENT_H
#define KEYRELEASEEVNT_H

#include "event.h"
#include "../input/keyboard.h"
namespace Events
{
    class KeyRepeatEvent : public Event
    {
    public:
        KeyRepeatEvent(Input::Key key)
        {
            this->Key = key;
        }

        ~KeyRepeatEvent() {}

        Input::Key Key;
    };
}

#endif // !KEYRELEASEEVENT_H
