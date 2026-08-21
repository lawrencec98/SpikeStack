#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP


#include "Event.hpp"
#include "EventQueue.hpp"
#include "InputNeuron.hpp"
#include "LifNeuron.hpp"


class EventDispatcher
{
public:
    void Push(spikestack::Event);

private:
    spikestack::Event_sp PopFromEventQueue();

    void ProcessEvent(spikestack::Event event);

    void ProcessSpike();
    double m_currentSimTime;

    std::shared_ptr<spikestack::EventQueue<spikestack::Event_sp>> m_queue;
    std::vector<std::shared_ptr<INeuron>> m_neurons;
};



#endif // EVENT_DISPATCHER_HPP