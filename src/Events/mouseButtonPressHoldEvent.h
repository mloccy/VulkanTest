#ifndef MOUSEBUTTONPRESSHOLDEVENT_H
#define MOUSEBUTTONPRESSHOLDEVENT_H

#include "mouseEvent.h"

#include "../Input/mouse.h"
namespace Events
{
    class MouseButtonPressHoldEvent : public MouseEvent
    {
    public:

        MouseButtonPressHoldEvent(Input::MouseButton button)
        {
            this->Button = button;
        }

        Input::MouseButton Button;
    };
}

#endif // !MOUSEBUTTONPRESSHOLDEVENT_H