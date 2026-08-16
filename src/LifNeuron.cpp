#include "LifNeuron.hpp"



LifNeuron::LifNeuron(LifNeuronInfo info)
    :   m_leakageRate(info.leakage_rate),
        m_vRest(info.vrest),
        m_vThreshold(info.vthreshold),
        m_vReset(info.vreset),
        m_vMin(info.vmin),
        m_vMax(info.vmax),
        m_vFiredSpike(info.vfiredSpike),
        m_vInstantaneous(m_vRest), //Start off at rest
        m_lastSpikeTime(std::chrono::steady_clock::now()),
        m_refactoryPeriod(info.refactoryPeriod)
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
    // TODO: if tElapsedSinceLastSpike > time_constant : just skip the accumulation bit.
    LifNeuron::UpdateInstantaneousVoltage();

    if (std::chrono::steady_clock::now() - m_refactoryPeriodStartTime < m_refactoryPeriod)
    {
        // do something
        // make it harder for the incoming spike to have effect on m_vInstantaneous
    }

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
    float spikeV = 1; // TODO CHANGE ME
    
    for (auto& it : m_connectedNeurons)
    {
        it->PushSpike(spikeV);
    }

    m_vInstantaneous = m_vReset;
    m_refactoryPeriodStartTime = std::chrono::steady_clock::now();
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


float LifNeuron::GetVoltageRest() const
{
    return m_vRest;
}

float LifNeuron::GetVoltageThreshold() const
{
    return m_vThreshold;
}

float LifNeuron::GetVoltageReset() const
{
    return m_vReset;
}

float LifNeuron::GetVoltageInstantaneous() const
{
    std::lock_guard<std::mutex> lock(m_mutexVInstantaneous);
    return m_vInstantaneous;
}

float LifNeuron::GetLeakageRate() const
{
    return m_leakageRate;
}

float LifNeuron::GetVoltageMin() const
{
    return m_vMin;
}

float LifNeuron::GetVoltageMax() const
{
    return m_vMax;
}

std::chrono::duration<double> LifNeuron::GetVoltageRefactoryPeriod() const
{
    return m_refactoryPeriod;
}