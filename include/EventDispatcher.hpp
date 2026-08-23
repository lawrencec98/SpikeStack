#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP


#include "Event.hpp"
#include "EventQueue.hpp"
#include "INeuron.hpp"
#include "Synapse.hpp"


namespace spikestack
{

    
class EventDispatcher
{
public:
    void Push(spikestack::Event);

private:
    Event_sp PopFromEventQueue();

    void ProcessEvent(Event event);

    void ProcessSpikeEvent(Event event);
    Time m_currentSimTime;

    std::shared_ptr<EventQueue<Event_sp>> m_queue;
    std::vector<std::shared_ptr<INeuron>> m_neurons;
};


}//namespace spikestack


#endif // EVENT_DISPATCHER_HPP