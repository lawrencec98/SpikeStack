#ifndef LIF_NEURON_HPP
#define LIF_NEURON_HPP

#include <chrono>
#include <memory>
#include <mutex>
#include <vector>

#include "INeuron.hpp"
#include "Spike.hpp"


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
    float vrest = -65.0;
    float vthreshold = -60.0;
    float vreset = -75.0;
    float vmin = -1.0;
    float vmax = 1.0;
    float leakageRate;
    float vSpike = 100;
    std::chrono::duration<double> absoluteRefactoryPeriod;
};


class LifNeuron : public INeuron
{
public:
    LifNeuron(LifNeuronInfo info);
    LifNeuron(const LifNeuron&) = delete;
    LifNeuron& operator=(const LifNeuron&) = delete;

    ~LifNeuron();

    void PushSpike(spike::Spike spike) override;
    void Fire() override;

    float GetVoltageRest() const;
    float GetVoltageThreshold() const;
    float GetVoltageReset() const;
    float GetVoltageInstantaneous() const;
    float GetLeakageRate() const;
    float GetVoltageMin() const;
    float GetVoltageMax() const;
    std::chrono::duration<double> GetVoltageRefactoryPeriod() const;


private:
    /**
     * @brief This function updates the instantaneous voltage of this neuron based on
     * time since last spike and leakage rate.
     */
    void UpdateInstantaneousVoltageOnPushSpike();

    /**
     * @brief This function returns the voltage of a spike, which is determined by the spike's polarity and synaptic weight.
     */
    float CalculateSpikeVoltage(bool isPositve);

    long int m_neuronId;

    float m_vRest = -65.0 ; //[mV]
    float m_vThreshold = -60.0; //[mV]
    float m_vReset = -75.0; //[mV]
    float m_vInstantaneous; //[mV]

    float m_leakageRate; //[mV/ms]
    float m_timeConstant; //[ms]

    const float m_vMin = -1.0; //Should this be const?
    const float m_vMax = 1.0; //Should this be const?

    const float m_vSpike = 100; //[mV]

    std::vector<std::shared_ptr<INeuron>> m_connectedNeurons;
    std::vector<float> m_synapticWeights; // Strength of the connection between this neuron and its synaptic pairs.

    std::chrono::time_point<std::chrono::steady_clock> m_lastSpikeTime;

    const std::chrono::duration<double> m_absoluteRefactoryPeriod = std::chrono::duration<double>(2); // We are simplifying things by only implementing abs refactory period, and not relative factory periods.
    std::chrono::time_point<std::chrono::steady_clock> m_refactoryPeriodStartTime;

    mutable std::mutex m_mutexLastSpikeTime;
    mutable std::mutex m_mutexVInstantaneous;
};

#endif //LIF_NEURON_HPP