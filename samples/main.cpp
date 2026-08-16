#include <iostream>

#include "LifNeuron.hpp"

int main()
{
    LifNeuronInfo info;
    info.leakageRate = 0.25;
    info.refactoryPeriod = std::chrono::milliseconds(10);
    info.vfiredSpike = 0.05;
    info.vmin = -1;
    info.vmin = 2;
    info.vreset = -0.65;
    info.vthreshold = -0.5;

    std::vector<std::unique_ptr<LifNeuron>> myNeurons;

    for (int i = 0; i < 100; i++)
    {
        myNeurons.push_back(std::move(std::make_unique<LifNeuron>(info))); 
    }

    std::cout << "Hello world" << std::endl;

    /*
        A  B  C  D
    A   0  1  1  0 
    B   0  0  1  0 
    C   1  1  0  1
    D   1  1  1  0   
    
    */
    std::vector<std::vector<bool>> adjacencyMatrix;

}