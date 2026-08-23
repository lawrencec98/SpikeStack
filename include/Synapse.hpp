#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include <memory>

#include "INeuron.hpp"
#include "Types.hpp"


namespace spikestack
{
    

class Synapse
{
public:
    Synapse(NeuronId pre, NeuronId post, double weight);
    ~Synapse();
    void PushSpike(spike::Spike spike, Time current_simtime);
    double CalculateSpikeVoltage(spike::Spike spike);
    NeuronId getPreNeuron() const;
    NeuronId getPostNeuron() const;
private:
    spike::Polarity synapsePolarity; // not sure about this one, spike and synapse probably shouldn't share teh same type
    NeuronId m_preNeuron;
    NeuronId m_postNeuron;
    double m_synapticWeight;
};


} //namespace spikestack



#endif // SYNAPSE_HPP