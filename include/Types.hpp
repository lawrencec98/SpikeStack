#ifndef TYPES_HPP
#define TYPES_HPP


#include <cstdint>


namespace spikestack
{


    using NeuronId = std::uint32_t;

    using SynapseId = std::uint32_t;

    using Time = double;


    struct LifNeuronInfo
    {
        float vrest = -65.0;
        float vthreshold = -60.0;
        float vreset = -75.0;
        float vmin = -1.0;
        float vmax = 1.0;
        float leakageRate;
        float vSpike = 100;
        Time absoluteRefactoryPeriod;
    };
}



#endif // TYPES_HPP