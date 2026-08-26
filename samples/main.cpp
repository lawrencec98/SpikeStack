#include <iostream>

#include "EventDispatcher.hpp"
#include "EventQueue.hpp"
#include "LifNeuron.hpp"
#include "Types.hpp"

using namespace spikestack;


int main()
{
    std::shared_ptr<EventQueue<std::shared_ptr<Event>, EventComparator>> queue_sp = std::make_shared<EventQueue<std::shared_ptr<Event>, EventComparator>>();
    
    spikestack::EventDispatcher dispatcher(queue_sp);


    spikestack::LifNeuronInfo info;
    info.leakageRate = 0.25;
    info.absoluteRefactoryPeriod = 10;
    info.vSpike = 0.05;
    info.vmin = -1;
    info.vmin = 2;
    info.vreset = -0.65;
    info.vthreshold = -0.5;

    // std::vector<std::unique_ptr<LifNeuron>> myNeurons;
    std::vector<float> adj;

    // for (int i = 0; i < 100; i++)
    // {
    //     myNeurons.push_back(std::move(std::make_unique<LifNeuron>(info, adj))); 
    // }

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