#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include <memory>

#include "INeuron.hpp"
#include "Types.hpp"


namespace spikestack
{

    
enum class SynapseType
{
    excitatory,
    inhibitory
};
    

struct SynapseInfo
{
    SynapseType type;
    NeuronId pre;
    NeuronId post;
    double weight;
    Time delay;
};


class Synapse
{
public:

    Synapse(SynapseInfo info);
    Synapse(NeuronId pre, NeuronId post, double weight, SynapseType type, Time delay);
    ~Synapse();

    /**
     * @brief Process and update the spike with weight and delay information
     */
    void ProcessSpike(std::shared_ptr<spike::Spike> spike, Time current_simtime);
    NeuronId GetPreNeuron() const;
    NeuronId GetPostNeuron() const;
    // SynapseType GetType() const;
private:
    SynapseType m_type; // not sure about this one, spike and synapse probably shouldn't share teh same type
    NeuronId m_pre;
    NeuronId m_post;
    double m_weight;
    Time m_delay;
};


} //namespace spikestack



#endif // SYNAPSE_HPP