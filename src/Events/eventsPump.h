#ifndef EVENTPUMP_H
#define EVENTPUMP_H
#include "event.h"
#include "iEventHandler.h"
#include <vector>

namespace Events
{
    class EventPump
    {
    public:
        static EventPump * GetInstance()
        {
            if (instance == nullptr)
            {
                instance = new EventPump();
            }
            return instance;
        }

        static void RegisterHandler(IEventHandler * evtHandler)
        {
            GetInstance()->registerHandler(evtHandler);
        }

        static void FireEvent(Event * evt)
        {
            GetInstance()->fireEvent(evt);
        }

    private:
        EventPump() {}

        void fireEvent(Event * evt);

        void registerHandler(IEventHandler * handler);

        static EventPump * instance;

        std::vector<IEventHandler *> handlers;
    };
}
#endif // !EVENTPUMP_H
