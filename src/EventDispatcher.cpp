#include "EventDispatcher.hpp"

using namespace spikestack;


EventDispatcher::EventDispatcher()
:   m_currentSimTime(0)
{

}


std::shared_ptr<Event> EventDispatcher::PopFromEventQueue()
{
    std::shared_ptr<Event> event = m_queue->PopEvent();
    
    ProcessEvent(event);
}


void EventDispatcher::ProcessEvent(std::shared_ptr<Event> event)
{
    switch(event->type)
    {
        case spikestack::EventType::Spike:
            ProcessSpikeEvent(event);
    }
}


void EventDispatcher::ProcessSpikeEvent(std::shared_ptr<Event> event)
{
    //TODO
    // SynapseId dest_synapse = event->destination;

    // std::vector<SynapseId> dest_synapses = dest_synapse->GetPostSynapses();

    // for (auto& syn : dest_synapses)
    // {
    //     syn->ProcessSpike() // TODO needs spike information.
    // }
}