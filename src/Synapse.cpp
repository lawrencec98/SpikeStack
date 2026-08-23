#include "Synapse.hpp"

using namespace spikestack;


Synapse::Synapse(std::shared_ptr<INeuron> pre, std::shared_ptr<INeuron> post, double weight)
:   m_preNeuron(pre),
    m_postNeuron(post),
    m_synapticWeight(weight)
{

}


Synapse::~Synapse()
{
    // Nothing yet.
}


void Synapse::PushSpike(spike::Spike spike, double current_simtime)
{
    m_postNeuron->PushSpike(spike, current_simtime);
}


double Synapse::CalculateSpikeVoltage(spike::Spike spike)
{
    double v = (spike.polarity == spike::Polarity::positive ? 1 : 0);

    return  v * m_synapticWeight;
}