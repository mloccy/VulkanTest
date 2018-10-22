#include "eventsPump.h"
namespace Events
{
    EventPump * EventPump::instance = nullptr;
    void EventPump::registerHandler(IEventHandler * evtHandler)
    {
        this->handlers.push_back(evtHandler);
    }

    void EventPump::fireEvent(Event * evt)
    {
        for (const auto & handler : handlers)
        {
            handler->HandleEvent(evt);
        }

        delete evt;
    }
}