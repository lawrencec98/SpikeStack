#include "EventDispatcher.hpp"

using namespace spikestack;


EventDispatcher::EventDispatcher(std::shared_ptr<EventQueue<std::shared_ptr<Event>, EventComparator>> queue)
:   m_currentSimTime(0),
    m_queue(queue)
{

}


std::shared_ptr<Event> EventDispatcher::PopFromEventQueue()
{
    std::shared_ptr<Event> event = m_queue->PopEvent();

    m_currentSimTime = event->occurence_timestamp; // simtime skips to the occurence time of popped event.
    
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

    // std::shared_ptr<Synapse> destSynapse = network->GetSynapseById(dest_synapse);

    // // destSynapse->ProcessSpike()


    // std::vector<SynapseId> dest_synapses = dest_synapse->GetPostSynapses();

    // for (auto& syn : dest_synapses)
    // {
    //     syn->ProcessSpike() // TODO needs spike information.
    // }
}