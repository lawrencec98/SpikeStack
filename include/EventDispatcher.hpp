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
    EventDispatcher();
    void Push(spikestack::Event);

private:
    std::shared_ptr<Event> PopFromEventQueue();

    void ProcessEvent(std::shared_ptr<Event> event);

    void ProcessSpikeEvent(std::shared_ptr<Event> event);
    Time m_currentSimTime;

    std::shared_ptr<EventQueue<std::shared_ptr<Event>>> m_queue;
    std::vector<std::shared_ptr<INeuron>> m_neurons;
};


}//namespace spikestack


#endif // EVENT_DISPATCHER_HPP