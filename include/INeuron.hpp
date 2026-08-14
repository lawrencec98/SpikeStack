#ifndef I_NEURON_HPP
#define I_NEURON_HPP


class INeuron
{
public:
    virtual ~INeuron();

    virtual void PushSpike(float spikeVoltage) = 0;
    
    virtual void Fire() = 0;
};


#endif // I_NEURON_HPP