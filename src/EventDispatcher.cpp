#include "EventDispatcher.hpp"


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
            ProcessSpike();
    }
}


void EventDispatcher::ProcessSpike()
{

}