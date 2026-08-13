#ifndef LIF_NEURON_HPP
#define LIF_NEURON_HPP

#include <chrono>
#include <memory>
#include <mutex>
#include <vector>

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
    float vmin;
    float vfiredSpike;
    float leakage_rate;
    std::vector<std::shared_ptr<LifNeuron>> connectedNeurons;
    std::chrono::duration<double> refactoryPeriod;
};


class LifNeuron : public INeuron
{
public:
    LifNeuron(LifNeuronInfo info);

    ~LifNeuron();

    void PushSpike(float spikeVoltage);
    void Fire();

private:

    /*
    @brief This function updates the instantaneous voltage of this neuron based on
    time since last spike and leakage rate.
    */
    void UpdateInstantaneousVoltage();

    float m_vRest;
    float m_vThreshold;
    float m_vReset;
    float m_vInstantaneous;

    float m_leakageRate;

    const float m_vMin;
    const float m_vFiredSpike;

    std::vector<std::shared_ptr<LifNeuron>> m_connectedNeurons;

    std::chrono::time_point<std::chrono::steady_clock> m_lastSpikeTime;

    std::chrono::duration<double> m_refactoryPeriod;

    std::mutex m_mutexLastSpikeTime;
    std::mutex m_mutexVInstantaneous;
};

#endif //LIF_NEURON_HPP