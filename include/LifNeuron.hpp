#ifndef LIF_NEURON_HPP
#define LIF_NEURON_HPP

#include <memory>
#include <mutex>
#include <vector>

#include "INeuron.hpp"

#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "Spike.hpp"
#include "Synapse.hpp"
#include "Types.hpp"


namespace spikestack
{

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
    Time absoluteRefactoryPeriod;
};


class LifNeuron : public INeuron
{
public:
    LifNeuron(std::shared_ptr<EventDispatcher> dispatcher, Time current_simtime, LifNeuronInfo info, std::vector<float> neuronAdjMatrix);
    LifNeuron(const LifNeuron&) = delete;
    LifNeuron& operator=(const LifNeuron&) = delete;

    ~LifNeuron();

    /**
     * @brief Processes an incoming spike and updates internal states of this neuron.
     */
    void PushSpike(spike::Spike spike, Time current_simtime) override;
    
    /**
     * @brief Prepares a spike then pushes it to the EventQueue.
     */
    void Fire(Time sim_time) override;

    float GetVoltageRest() const;
    float GetVoltageThreshold() const;
    float GetVoltageReset() const;
    float GetVoltageInstantaneous() const;
    float GetLeakageRate() const;
    float GetVoltageMin() const;
    float GetVoltageMax() const;
    Time GetVoltageRefactoryPeriod() const;
    std::vector<std::shared_ptr<Synapse>> GetPreSynapses() const override;
    std::vector<std::shared_ptr<Synapse>> GetPostSynapses() const override;

private:
    /**
     * @brief This function updates the instantaneous voltage of this neuron based on
     * time since last spike and leakage rate.
     */
    void SimulateLeakedVoltage(double sim_time);

    /**
     * @brief TODO: This function returns the voltage of a spike, which is determined by the spike's polarity and synaptic weight.
     */
    float CalculateSpikeVoltage(bool isPositve);

    std::shared_ptr<EventDispatcher> m_dispatcher;

    unsigned long int m_neuronId;

    float m_vRest = -65.0 ; //[mV]
    float m_vThreshold = -60.0; //[mV]
    float m_vReset = -75.0; //[mV]
    float m_vInstantaneous; //[mV]

    float m_leakageRate; //[mV/ms]
    float m_timeConstant; //[ms]

    const float m_vMin = -1.0; //Should this be const?
    const float m_vMax = 1.0; //Should this be const?

    const float m_vSpike = 100; //[mV]

    std::vector<std::shared_ptr<Synapse>> m_postSynapses;
    std::vector<std::shared_ptr<Synapse>> m_preSynapses;
    // std::vector<std::shared_ptr<INeuron>> m_connectedNeurons;
    std::vector<float> m_synapticWeights; // Strength of the connection between this neuron and its synaptic pairs.

    double m_lastSpikeTime;

    const double m_absoluteRefactoryPeriod = 2; // We are simplifying things by only implementing abs refactory period, and not relative factory periods.
    double m_refactoryPeriodStartTime;
};


} //namespace spikestack
#endif //LIF_NEURON_HPP