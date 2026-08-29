#include "Network.hpp"

#include <numeric>


using namespace spikestack;



Network::Network()
{

}


Network::~Network()
{

}


void Network::AddPopulation(int size)
{
    int numSynapses = (size * (size - 1)) / 2;

    std::vector<SynapseId> vecSynapseIds(size - 1); // Each neuron is connected to size-1 neurons.
    std::iota(vecSynapseIds.begin(), vecSynapseIds.end(), 0); // TODO: How to know which Ids to use?

    LifNeuronInfo info {};
    info.leakageRate = 0.25;
    info.absoluteRefactoryPeriod = 10;
    info.vSpike = 0.05;
    info.vmin = -1;
    info.vmin = 2;
    info.vreset = -0.65;
    info.vthreshold = -0.5;

    // for (int i = 0; i < size; ++i)
    // {
    //     m_neuronPopulation.push_back(LifNeuron(info, ));
    // }
}


void Network::Connect()
{
    if (m_neuronPopulation.empty() || m_synapsePopulation.empty())
    {
        throw std::runtime_error("Error - cannot connect empty nodes.");
    }

    //TODO: look for all-to-all network connecting algorithm.
}


// std::shared_ptr<Synapse> Network::GetSynapseById(SynapseId id)
// {
//     return m_synapsePopulation[id];
// }