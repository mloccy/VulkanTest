#ifndef KEYRELEASEEVENT_H
#define KEYRELEASEEVNT_H

#include "event.h"
#include "../input/keyboard.h"
namespace Events
{
    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(Input::Key key)
        {
            this->Key = key;
        }

        ~KeyReleaseEvent() {}

        Input::Key Key;
    };
}

#endif // !KEYRELEASEEVENT_H
