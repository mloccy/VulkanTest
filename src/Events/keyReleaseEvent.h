#ifndef KEYRELEASEEVENT_H
#define KEYRELEASEEVENT_H

#include "keyEvent.h"
#include "../Input/keyboard.h"
namespace Events
{
    class KeyReleaseEvent : public KeyEvent
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
