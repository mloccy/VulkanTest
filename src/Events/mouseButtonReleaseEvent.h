#ifndef MOUSEBUTTONRELEASEEVENT_H
#define MOUSEBUTTONRELEASEEVENT_H

#include "mouseEvent.h"

#include "../Input/mouse.h"
namespace Events
{
    class MouseButtonReleaseEvent : public MouseEvent
    {
    public:

        MouseButtonReleaseEvent(Input::MouseButton button)
        {
            this->Button = button;
        }

        Input::MouseButton Button;
    };
}

#endif // !MOUSEBUTTONRELEASEEVENT_H