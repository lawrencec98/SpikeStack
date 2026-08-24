#ifndef SPIKE_HPP
#define SPIKE_HPP

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

struct Spike
{
    NeuronId source_id;
    Time occ_time; // The point at which the neuron exceeded v_threshold.
    Time delivered_time; // This factors in synaptic delay.
    double weight;
};


} //namespace spike
} //namespace spikestack


#endif // SPIKE_HPP