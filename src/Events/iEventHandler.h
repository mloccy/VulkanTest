#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H
#include "event.h"

namespace Events
{
    class IEventHandler
    {
    public:

        virtual void HandleEvent(Event * evt) = 0;
    };
}

#endif // !IEVENTHANDLER_H
