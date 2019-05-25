#ifndef MOUSEMOVEEVENT_H
#define MOUSEMOVEEVENT_H

#include "mouseEvent.h"

namespace Events
{
    class MouseMoveEvent : public MouseEvent
    {
    public:

        double X;
        double Y;

        MouseMoveEvent(double x, double y)
        {
            this->X = x; this->Y = y;
        }
    };
}

#endif // !MOUSEBUTTONPRESSEVENT_H