#ifndef EVENT_HPP
#define EVENT_HPP


#include "EventType.hpp"



namespace spikestack
{

    // TODO: Pretty sure i should embed the actual spike in here as well...
    struct Event
    {
        spikestack::EventType type;
        double timestamp;
        std::shared_ptr<INeuron> destination;
    };

} //namespace spikestack


#endif //EVENT_HPP