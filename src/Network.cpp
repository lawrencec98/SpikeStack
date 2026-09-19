#include "Network.hpp"

#include <numeric>
#include <stdexcept>


using namespace spikestack;



Network::Network()
{

}


Network::~Network()
{

}


void Network::AddPopulation(std::string name, int size, LifNeuronInfo info)
{
    // Create a population group
    Population pop {
        .start = (m_neurons.size() > 0) ? m_neurons.size() - 1 : 0,
        .size = size,
        .name = name // User will connect populations by name.
    };

    m_populations.push_back(pop);


    // Create new neurons
    for (int i = 0; i < size; ++i)
    {
        m_neurons.emplace_back(std::make_shared<LifNeuron>(info));
        m_mapOutputSynapses.push_back(std::vector<SynapseId>{}); // Reserve a vector of synapses for this neuron
    }
}


void Network::Connect(std::string popName1, std::string popName2, SynapseInfo info)
{
    if (m_neurons.empty())
    {
        throw std::runtime_error("Error - cannot connect empty nodes.");
    }

    //TODO: look for all-to-all network connecting algorithm.

    // Step 1: Find population indexes
    Population pop1 = FindPopulation(popName1);
    Population pop2 = FindPopulation(popName2);

    // Create all-to-all connections (represented by Synapses)
    for (int i = 0; i < pop1.size; i++)
    {
        for (int j = 0; j < pop2.size; j++)
        {
            // Create synapse
            info.pre = pop1.start + i;
            info.post = pop2.start + j;
            m_synapses.emplace_back(std::make_shared<Synapse>(info));

            // Store Neuron->Synapse mapping
            SynapseId id = m_synapses.size() - 1;
            m_mapOutputSynapses.at(pop1.start + i).push_back(id);

            // m_mapOutputSynapses usage would be like: Dispatcher.ProcessSpike(m_mapOutputSynapses[spike.src])
        }
    }
}



Population Network::FindPopulation(std::string name)
{
    for (const auto& pop : m_populations)
    {
        if (pop.name == name)
        {
            return pop;
        }
    }
    
    throw std::runtime_error("Error: Could not find population.");
}


std::vector<std::shared_ptr<Synapse>> Network::GetSynapses() const
{
    return m_synapses;
}

// std::shared_ptr<Synapse> Network::GetSynapseById(SynapseId id)
// {
//     return m_synapsePopulation[id];
// }