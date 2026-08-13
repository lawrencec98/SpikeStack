#include "LifNeuron.hpp"



LifNeuron::LifNeuron(LifNeuronInfo info)
    :   m_leakageRate(info.leakage_rate),
        m_vRest(info.vrest),
        m_vThreshold(info.vthreshold),
        m_vReset(info.vreset),
        m_vMin(info.vmin),
        m_vFiredSpike(info.vfiredSpike),
        m_vInstantaneous(m_vRest), //Start off at rest
        m_lastSpikeTime(std::chrono::steady_clock::now())
{
    //TODO add config parsing.
}


LifNeuron::~LifNeuron()
{
    // TODO
}


/**
 * This input signal is 'digital', scaled by the synaptic weight.
 */
void LifNeuron::PushSpike(float spikeVoltage)
{
    // accumulate into m_vInstantaneous (note it can be +ve or -ve)
    LifNeuron::UpdateInstantaneousVoltage();

    std::lock_guard<std::mutex> lockvInst(m_mutexVInstantaneous);
    m_vInstantaneous += spikeVoltage;

    if (m_vInstantaneous >= m_vThreshold)
    {
        LifNeuron::Fire();
    }

    {
        std::lock_guard<std::mutex> lockLastSpikeTime(m_mutexLastSpikeTime);
        m_lastSpikeTime = std::chrono::steady_clock::now();
    }
}


void LifNeuron::Fire(/*destination neuron*/)
{
    // send a spike to all? or some? connected neurons
    float spikeV = 0.5; // TODO CHANGE ME
    
    for (auto& it : m_connectedNeurons)
    {
        it->PushSpike(spikeV);
    }

    m_vInstantaneous = m_vReset;
    // TODO start the vRefactoryPeriod countdown
}


void LifNeuron::UpdateInstantaneousVoltage()
{
    std::chrono::steady_clock::time_point tNow = std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration tElapsedSinceLastSpike;
    {
        std::lock_guard<std::mutex> lockLastSpikeTime(m_mutexLastSpikeTime);
        tElapsedSinceLastSpike = tNow - m_lastSpikeTime;
    }
    
    float tElapsedFloat = std::chrono::steady_clock::duration(tElapsedSinceLastSpike).count();

    float voltageLeaked = tElapsedFloat * m_leakageRate;

    {
        std::lock_guard<std::mutex> lockvInst(m_mutexVInstantaneous);
        float vInst = m_vInstantaneous - voltageLeaked;
        m_vInstantaneous = std::max(m_vMin, vInst);
    }
}