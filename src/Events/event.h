#ifndef EVENT_H
#define EVENT_H

namespace Events
{
    class Event
    {
    public:
        virtual ~Event() {}
    protected:
        Event() {}
    };
}
#endif // !EVENT_H