#include <iostream>

#include "EventDispatcher.hpp"
#include "EventQueue.hpp"
#include "LifNeuron.hpp"
#include "Types.hpp"

using namespace spikestack;


int main()
{
    // Set up an event queue
    std::shared_ptr<EventQueue<std::shared_ptr<Event>, EventComparator>> queue_sp = std::make_shared<EventQueue<std::shared_ptr<Event>, EventComparator>>();
    
    // Create an Event Dispatcher and give ownership of the event queue.
    EventDispatcher dispatcher(queue_sp);

    // Create a synapse population (population is only 1 in this case)
    SynapseInfo synInfo {};
    synInfo.delay = 2;
    synInfo.post = 1;
    synInfo.pre = 0;
    synInfo.type = SynapseType::excitatory;
    synInfo.weight = 0.5;

    // Create a population of neurons and give it the synapses
    LifNeuronInfo info {};
    info.leakageRate = 0.25;
    info.absoluteRefactoryPeriod = 10;
    info.vSpike = 0.05;
    info.vmin = -1;
    info.vmin = 2;
    info.vreset = -0.65;
    info.vthreshold = -0.5;


    std::shared_ptr<Network> network = std::make_shared<Network>();
    dispatcher.AddNetwork(network);

    dispatcher.m_network->AddPopulation("input", 10, info);
    dispatcher.m_network->AddPopulation("output", 10, info);

    dispatcher.m_network->Connect("input", "output", synInfo);


    // FOR LOGGING ONLY!
    // auto synapsesVector = dispatcher.m_network->GetSynapses();
    // int i = 1;
    // for (const auto& syn : synapsesVector)
    // {
    //     int pre = syn->GetPreNeuron();
    //     int post = syn->GetPostNeuron();

    //     std::cout << "Synapse" << " i: " << pre << " " << post << std::endl;
    //     i++;
    // }

}