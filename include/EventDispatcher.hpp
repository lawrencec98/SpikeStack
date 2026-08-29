#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP


#include "Event.hpp"
#include "EventQueue.hpp"
// #include "Network.hpp"
#include "INeuron.hpp"
#include "Synapse.hpp"


namespace spikestack
{

    
class EventDispatcher
{
public:
    EventDispatcher(std::shared_ptr<EventQueue<std::shared_ptr<Event>, EventComparator>> queue);
    void Push(Event);

private:
    std::shared_ptr<Event> PopFromEventQueue();

    void ProcessEvent(std::shared_ptr<Event> event);

    void ProcessSpikeEvent(std::shared_ptr<Event> event);
    Time m_currentSimTime; // need to update this whenever we pop from the eventqueue.

    std::shared_ptr<EventQueue<std::shared_ptr<Event>, EventComparator>> m_queue;
    std::vector<std::shared_ptr<INeuron>> m_neurons;
    // std::shared_ptr<Network> network; // does eventdispatcher own network?
};


}//namespace spikestack


#endif // EVENT_DISPATCHER_HPP