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
    std::vector<Synapse> vecSynapse;
    SynapseInfo synInfo {};
    synInfo.delay = 2;
    synInfo.post = 1;
    synInfo.pre = 0;
    synInfo.type = SynapseType::excitatory;
    synInfo.weight = 0.5;

    Synapse synapse1(synInfo);
    vecSynapse.push_back(synapse1);


    // Create a population of neurons and give it the synapses
    LifNeuronInfo info {};
    info.leakageRate = 0.25;
    info.absoluteRefactoryPeriod = 10;
    info.vSpike = 0.05;
    info.vmin = -1;
    info.vmin = 2;
    info.vreset = -0.65;
    info.vthreshold = -0.5;


    std::vector<std::unique_ptr<LifNeuron>> myNeurons;
    std::vector<float> adj;

    // for (int i = 0; i < 3; i++)
    // {
    //     myNeurons.push_back(std::move(std::make_unique<LifNeuron>(info, adj))); 
    // }

    // TODO: I need to fix the dependencies here. Currently it is weird for synapses to know their neyrons, and for neurons to know their synapses.
    // I feel like only one of them should know the other.

    // std::cout << "Hello world" << std::endl;

    // /*
    //     A  B  C  D
    // A   0  1  1  0 
    // B   0  0  1  0 
    // C   1  1  0  1
    // D   1  1  1  0   
    
    // */
    // std::vector<std::vector<bool>> adjacencyMatrix;

}