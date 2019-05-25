#ifndef KEYHOLDEVENT_H
#define KEYHOLDEVENT_H

#include "keyEvent.h"

#include "../input/keyboard.h"
namespace Events
{
    class KeyHoldEvent : public KeyEvent
    {
    public:
        KeyHoldEvent(Input::Key key)
        {
            this->Key = key;
        }

        ~KeyHoldEvent() {}

        Input::Key Key;
    };
}

#endif // !KEYRELEASEEVENT_H
