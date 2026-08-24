#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

#include "EventType.hpp"
#include "Types.hpp"


namespace spikestack
{


// TODO: Pretty sure i should embed the actual spike in here as well...
struct Event
{
    spikestack::EventType type;
    Time occurence_timestamp;
    SynapseId destination;
};



} //namespace spikestack


#endif //EVENT_HPP