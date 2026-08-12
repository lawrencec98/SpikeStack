#ifndef I_NEURON_HPP
#define I_NEURON_HPP


class INeuron
{
public:
    virtual ~INeuron();

    virtual void pushInput() = 0;
    
    virtual void fire() = 0;
};


#endif // I_NEURON_HPP