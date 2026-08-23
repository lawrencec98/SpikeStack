#include "Synapse.hpp"

using namespace spikestack;


Synapse::Synapse(SynapseInfo info)
:   m_type(info.type),
    m_pre(info.pre),
    m_post(info.post),
    m_weight(info.weight),
    m_delay(info.delay)
{

}


Synapse::Synapse(NeuronId pre, NeuronId post, double weight, SynapseType type, Time delay)
:   m_type(type),
    m_pre(pre),
    m_post(post),
    m_weight(weight),
    m_delay(delay)
{

}


Synapse::~Synapse()
{
    // Nothing yet.
}


void Synapse::ProcessSpike(std::shared_ptr<spike::Spike> spike, double current_simtime)
{
    spike->delivered_time = spike->occ_time + m_delay;

    if (m_type == Synapse::SynapseType::excitatory)
    {
        spike->weight = 1 * m_weight;
    }
    else if (m_type == SynapseType::inhibitory)
    {
        spike->weight = -1 * m_weight;
    }
}