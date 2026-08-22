#ifndef I_NEURON_HPP
#define I_NEURON_HPP

#include "Spike.hpp"

namespace spikestack 
{

    class INeuron
    {
    public:
        virtual ~INeuron() = default;
        virtual void PushSpike(spike::Spike spike, double current_simtime) = 0;
        virtual void Fire(double sim_time) = 0;
    };


}//namespace spikestack


#endif // I_NEURON_HPP