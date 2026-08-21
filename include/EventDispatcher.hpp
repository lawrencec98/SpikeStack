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
    double m_currentSimTime;

    std::shared_ptr<spikestack::EventQueue<spikestack::Event>> m_queue;
    std::vector<std::shared_ptr<INeuron>> m_neurons;
};



#endif // EVENT_DISPATCHER_HPP