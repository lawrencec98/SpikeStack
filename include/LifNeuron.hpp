#ifndef LIF_NEURON_HPP
#define LIF_NEURON_HPP

#include <chrono>

#include "INeuron.hpp"


/*
Model of an LIF Neuron

-------------
Inputs:
    - Event (x, y, timestamp, polarity)
    - Binary ON OFF signal
-------------
Neuron state:
    - V_rest
    - V_threshold
    - V_reset
    - Integration
    - Leakage
    - Refactory period
-------------
Output:
    - Spike ON OFF signal.
-------------
*/

struct LifNeuronInfo
{
    float vrest;
    float vthreshold;
    float vreset;
    float leakage_rate;
};


class LifNeuron : public INeuron
{
public:
    LifNeuron(LifNeuronInfo info);

    ~LifNeuron();

    void push_input(float spikeVoltage);
    void fire();

private:
    float m_vRest;
    float m_vThreshold;
    float m_vReset;
    float m_vInstantaneous;

    float m_leakageRate;

    std::chrono::time_point<std::chrono::steady_clock> m_lastSpikeTime;

    std::chrono::duration<double> m_refactoryPeriod;
};

#endif //LIF_NEURON_HPP