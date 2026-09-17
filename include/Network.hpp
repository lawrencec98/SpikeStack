#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>


#include "LifNeuron.hpp"
#include "Synapse.hpp"
#include "Types.hpp"


namespace spikestack {


struct Population {
    int start;
    int size;
    std::string name;
};


// TODO: Only supports all-to-all neuron connection for now.
class Network 
{
public:
    Network();
    ~Network();

    void AddPopulation(std::string name, int size, LifNeuronInfo info);

    void Connect(std::string popName1, std::string popName2, SynapseInfo ifno);

    std::shared_ptr<Synapse> GetSynapseById(SynapseId id);

    Population FindPopulationByName(std::string name);

private:
    std::vector<std::shared_ptr<INeuron>> m_neurons;
    std::vector<std::shared_ptr<Synapse>> m_synapses;

    std::vector<std::vector<SynapseId>> m_mapOutputSynapses; // This maps a neuron to its output synapses

    std::vector<Population> m_populations;
};




} //namespace spikestack
#endif //NETWORK_HPP