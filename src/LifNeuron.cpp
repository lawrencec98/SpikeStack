#include "LifNeuron.hpp"

using namespace spikestack;

LifNeuron::LifNeuron(std::shared_ptr<EventDispatcher> dispatcher, double current_simtime, LifNeuronInfo info, std::vector<float> neuronAdjMatrix)
    :   m_dispatcher(dispatcher),
        m_leakageRate(info.leakageRate),
        m_timeConstant(1/m_leakageRate),
        m_vRest(info.vrest),
        m_vThreshold(info.vthreshold),
        m_vReset(info.vreset),
        m_vMin(info.vmin),
        m_vMax(info.vmax),
        m_vSpike(info.vSpike),
        m_vInstantaneous(m_vRest), //Start off at rest
        m_lastSpikeTime(current_simtime),
        m_absoluteRefactoryPeriod(info.absoluteRefactoryPeriod),
        m_refactoryPeriodStartTime(std::numeric_limits<double>::max())
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
void LifNeuron::PushSpike(spike::Spike spike, double current_simtime)
{
    LifNeuron::SimulateLeakedVoltage(current_simtime); //because we have not updated the value of m_InstantaneousVoltage since the last PushSpike event on this neuron.

    bool isPositive = (spike.polarity == spike::Polarity::positive);
    float spikeVoltage = LifNeuron::CalculateSpikeVoltage(isPositive);
    float newVInst = m_vInstantaneous + spikeVoltage;

    m_vInstantaneous = std::min(m_vMax, newVInst); // Make sure we don't go past max voltage.

    if (m_vInstantaneous >= m_vThreshold)
    {
        if (!(current_simtime - m_refactoryPeriodStartTime < m_absoluteRefactoryPeriod)) // If we were still within abs refactory period we would skip firing this spike.
        {
            Fire(current_simtime);
        }
    }

    m_lastSpikeTime = current_simtime;
}


void LifNeuron::Fire(double current_sim_time)
{
    // TODO: Note that neurons can connect to themself. We need to make sure that a neuron doesn't
    // recursively call Fire on itself forever.

    spike::Spike spike;
    spike.polarity = spike::Polarity::positive; // how do we decide if the outgoing spike should be positive or negative?
    spike.occ_time = current_sim_time;
    spike.delivered_time = spike.occ_time; // TODO figure out how to represent synaptic delay.
    spike.source_id = m_neuronId;
    
    for (auto& syn : m_preSynapses)
    {
        // spikestack::Event event;
        // event.occurence_timestamp = current_sim_time;
        // event.type = spikestack::EventType::Spike;
        // event.destination = syn->getPostNeuron();

        // m_dispatcher->Push(event);
    }

    m_vInstantaneous = m_vReset;
    m_refactoryPeriodStartTime = current_sim_time;
}


void LifNeuron::SimulateLeakedVoltage(double current_sim_time)
{
    double tElapsedSinceLastSpike = current_sim_time - m_lastSpikeTime;

    float voltageLeaked = tElapsedSinceLastSpike * m_leakageRate; // linear leakage model.

    float newVInst = m_vInstantaneous - voltageLeaked;

    m_vInstantaneous = std::max(m_vMin, newVInst);
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


double LifNeuron::GetVoltageRefactoryPeriod() const
{
    return m_absoluteRefactoryPeriod;
}


std::vector<std::shared_ptr<Synapse>> LifNeuron::GetPreSynapses() const
{
    return m_preSynapses;
}


std::vector<std::shared_ptr<Synapse>> LifNeuron::GetPostSynapses() const
{
    return m_postSynapses;
}