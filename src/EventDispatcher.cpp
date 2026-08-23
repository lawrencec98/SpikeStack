#include "EventDispatcher.hpp"

using namespace spikestack;

spikestack::Event_sp EventDispatcher::PopFromEventQueue()
{
    spikestack::Event event = m_queue->PopEvent();
    
    ProcessEvent(event);
}


void EventDispatcher::ProcessEvent(spikestack::Event event)
{
    switch(event.type)
    {
        case spikestack::EventType::Spike:
            ProcessSpikeEvent(event);
    }
}


void EventDispatcher::ProcessSpikeEvent(Event event)
{
    std::shared_ptr<INeuron> neuron = event.destination;

    std::vector<std::shared_ptr<Synapse>> dest_synapses = neuron->GetPostSynapses();

    for (auto& syn : dest_synapses)
    {
        syn->CalculateSpikeVoltage() // TODO needs spike information.
    }
}