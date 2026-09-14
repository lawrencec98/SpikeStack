#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "LifNeuron.hpp"
#include "Synapse.hpp"
#include "Types.hpp"


namespace spikestack {


struct Population {
    int start;
    int size;
};


// TODO: Only supports all-to-all neuron connection for now.
class Network 
{
public:
    Network();
    ~Network();

    Population AddPopulation(int size, LifNeuronInfo info);

    void Connect();

    std::shared_ptr<Synapse> GetSynapseById(SynapseId id);

private:
    std::vector<LifNeuron> m_neuronPopulation;
    std::vector<Synapse> m_synapsePopulation;

    std::vector<NeuronId> m_neuronIds;
    std::vector<SynapseId> m_synapseIds;

    std::vector<Population> m_populations;
};




} //namespace spikestack
#endif //NETWORK_HPP