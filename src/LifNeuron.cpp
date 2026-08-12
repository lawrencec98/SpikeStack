#include "LifNeuron.hpp"



LifNeuron::LifNeuron(LifNeuronInfo info)
    :   m_leakageRate(info.leakage_rate),
        m_vRest(info.vrest),
        m_vThreshold(info.vthreshold),
        m_vReset(info.vreset),
        m_vInstantaneous(m_vRest), //Start off at rest
        m_lastSpikeTime(std::chrono::steady_clock::now())
{

}


LifNeuron::~LifNeuron()
{
    // TODO
}


/**
 * This input signal is 'digital', scaled by the synaptic weight.
 */
void LifNeuron::push_input(float spikeVoltage)
{
    // accumulate into m_vInstantaneous (note it can be +ve or -ve)
    m_vInstantaneous += spikeVoltage;

    if (m_vInstantaneous >= m_vThreshold)
    {
        LifNeuron::fire();
    }

    m_vRest = m_vReset;
    m_lastSpikeTime = std::chrono::steady_clock::now();
    // TODO start the vRefactoryPeriod countdown
}