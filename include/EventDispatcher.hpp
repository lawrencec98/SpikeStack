#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP


#include "Event.hpp"
#include "EventQueue.hpp"
#include "INeuron.hpp"


namespace spikestack
{

    class EventDispatcher
    {
    public:
        void Push(spikestack::Event);

    private:
        spikestack::Event_sp PopFromEventQueue();

        void ProcessEvent(spikestack::Event event);

        void ProcessSpikeEvent();
        double m_currentSimTime;

        std::shared_ptr<spikestack::EventQueue<spikestack::Event_sp>> m_queue;
        std::vector<std::shared_ptr<INeuron>> m_neurons;
    };


}//namespace spikestack


#endif // EVENT_DISPATCHER_HPP