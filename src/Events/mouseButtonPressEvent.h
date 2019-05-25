#ifndef MOUSEBUTTONPRESSEVENT_H
#define MOUSEBUTTONPRESSEVENT_H

#include "mouseEvent.h"
#include "../Input/mouse.h"
namespace Events
{
    class MouseButtonPressEvent : public MouseEvent
    {
    public:

        MouseButtonPressEvent(Input::MouseButton button)
        {
            this->Button = button;
        }

        Input::MouseButton Button;
    };
}

#endif // !MOUSEBUTTONPRESSEVENT_H