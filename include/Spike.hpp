#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "Event.hpp"
#include "Types.hpp"


namespace spikestack
{
namespace spike 
{


enum class Polarity {
    positive,
    negative
};

struct InputSpike
{
    int x;
    int y;
    spike::Polarity polarity;
    Time timestamp;
};


struct Spike : public Event
{
    spikestack::EventType type;
    Time occurence_timestamp; // The point at which the neuron exceeded v_threshold.
    Time delivered_time; // This factors in synaptic delay.
    NeuronId src;
};


} //namespace spike
} //namespace spikestack


#endif // SPIKE_HPP