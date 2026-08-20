#include "LifNeuron.hpp"


LifNeuron::LifNeuron(LifNeuronInfo info, std::vector<float> neuronAdjMatrix)
    :   m_leakageRate(info.leakageRate),
        m_timeConstant(1/m_leakageRate),
        m_vRest(info.vrest),
        m_vThreshold(info.vthreshold),
        m_vReset(info.vreset),
        m_vMin(info.vmin),
        m_vMax(info.vmax),
        m_vSpike(info.vSpike),
        m_vInstantaneous(m_vRest), //Start off at rest
        m_lastSpikeTime(std::chrono::steady_clock::now()),
        m_absoluteRefactoryPeriod(info.absoluteRefactoryPeriod),
        m_refactoryPeriodStartTime(std::chrono::steady_clock::time_point::max())
{
    //TODO add config parsing.

    // TODO, use the neuronAdjacencyMatrix to populate m_connectedNeurons.

}


LifNeuron::~LifNeuron()
{
    // TODO
}


/**
 * @brief Accumulates incoming spikes into m_vInstantaneous (note it can be +ve or -ve),
 * factoring in synaptic weights. Then decides whether we should fire a neuron based on v_thresh.
 * @param spike [in] - An incoming spike sent by another neuron
 */
void LifNeuron::PushSpike(spike::Spike spike)
{
    LifNeuron::UpdateInstantaneousVoltageOnPushSpike(); //because we have not updated the value of m_InstantaneousVoltage since the last PushSpike event on this neuron.

    std::lock_guard<std::mutex> lockvInst(m_mutexVInstantaneous);
    std::lock_guard<std::mutex> lockLastSpikeTime(m_mutexLastSpikeTime);

    bool isPositive = (spike.polarity == spike::Polarity::positive);
    float spikeVoltage = LifNeuron::CalculateSpikeVoltage(isPositive);
    float newVInst = m_vInstantaneous + spikeVoltage;

    m_vInstantaneous = std::min(m_vMax, newVInst); // Make sure we don't go past max voltage.

    if (m_vInstantaneous >= m_vThreshold)
    {
        if (!(std::chrono::steady_clock::now() - m_refactoryPeriodStartTime < m_absoluteRefactoryPeriod)) // If we were still within abs refactory period we would skip firing this spike.
        {
            LifNeuron::Fire();
        }
    }

    m_lastSpikeTime = std::chrono::steady_clock::now();
}


void LifNeuron::Fire() //Send a spike to all? or some? connected neurons
{
    // TODO: Note that neurons can connect to themself. We need to make sure that a neuron doesn't
    // recursively call Fire on itself forever.

    //TODO CHANGE ALL OF THIS BIT.
    spike::Spike spike;
    spike.polarity = spike::Polarity::positive; // how do we decide if the outgoing spike should be positive or negative?
    spike.timestamp = std::chrono::steady_clock::now();
    spike.source_id = m_neuronId;
    
    for (auto& it : m_connectedNeurons)
    {
        it->PushSpike(spike);
    }

    m_vInstantaneous = m_vReset;
    m_refactoryPeriodStartTime = std::chrono::steady_clock::now();
}


void LifNeuron::UpdateInstantaneousVoltageOnPushSpike()
{
    std::chrono::steady_clock::duration tElapsedSinceLastSpike = std::chrono::steady_clock::now() - m_lastSpikeTime;

    float tElapsedFloat = std::chrono::steady_clock::duration(tElapsedSinceLastSpike).count();

    float voltageLeaked = tElapsedFloat * m_leakageRate; // linear leakage model.

    float newVInst = m_vInstantaneous - voltageLeaked;

    m_vInstantaneous = std::max(m_vMin, newVInst);
}


float LifNeuron::CalculateSpikeVoltage(bool isPositive)
{
    // TODO
    // Look into CSR - compressed sparse row. (save all col ids, save all values, only save row ptrs)

    //float weight = m_connectedNeurons & m_synapticWeights;

    //float result = m_vSpike * weight;
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
    return m_absoluteRefactoryPeriod;
}