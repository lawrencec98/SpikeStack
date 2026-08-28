#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "LifNeuron.hpp"
#include "Synapse.hpp"


namespace spikestack {


// TODO: Only supports all-to-all neuron connection for now.
class Network 
{
public:
    Network();
    ~Network();

    void AddPopulation(int size);

    void Connect();

private:
    std::vector<LifNeuron> m_neuronPopulation;
    std::vector<Synapse> m_synapsePopulation;
};




} //namespace spikestack
#endif //NETWORK_HPP