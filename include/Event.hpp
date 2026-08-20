#ifndef EVENT_HPP
#define EVENT_HPP


#include "EventType.hpp"



namespace spikestack
{

    class Event
    {
    public:
        Event();
        ~Event();
    private:
        spikestack::EventType m_type;
    };


} //namespace spikestack


#endif //EVENT_HPP