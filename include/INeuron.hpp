#ifndef I_NEURON_HPP
#define I_NEURON_HPP

#include "Spike.hpp"


class INeuron
{
public:
    virtual ~INeuron() = default;

    virtual void PushSpike(spike::Spike spike) = 0;
    
    virtual void Fire() = 0;
};


#endif // I_NEURON_HPP