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
    float vrest;
    float vthreshold;
    float vreset;
    float vmin;
    float vmax;
    float leakageRate;
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
    void UpdateInstantaneousVoltage();

    /**
     * @brief This function returns the voltage of a spike, which is determined by the spike's polarity and synaptic weight.
     */
    float CalculateSpikeVoltage(bool isPositve);

    float m_vRest; //unit: mV
    float m_vThreshold; //unit: mV
    float m_vReset; //unit: mV
    float m_vInstantaneous; //unit: mV

    float m_leakageRate; //unit: mV/ms
    float m_timeConstant; //unit: ms

    const float m_vMin; //Should this be const?
    const float m_vMax; //Should this be const?

    std::vector<std::shared_ptr<INeuron>> m_connectedNeurons;
    std::vector<float> m_synapticWeights; // Strength of the connection between this neuron and its synaptic pairs.

    std::chrono::time_point<std::chrono::steady_clock> m_lastSpikeTime;

    const std::chrono::duration<double> m_absoluteRefactoryPeriod; // We are simplifying things by only implementing abs refactory period, and not relative factory periods.
    std::chrono::time_point<std::chrono::steady_clock> m_refactoryPeriodStartTime;

    mutable std::mutex m_mutexLastSpikeTime;
    mutable std::mutex m_mutexVInstantaneous;
};

#endif //LIF_NEURON_HPP