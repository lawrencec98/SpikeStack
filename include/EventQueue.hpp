#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"

#include <deque>
#include <memory>
#include <mutex>


namespace spikestack
{
    template<typename event>
    class EventQueue
    {
    public:
        EventQueue();
        
        ~EventQueue();

        void PushEvent(event event);
        
        event PopEvent();

    private:
        std::deque<event> m_queue;
        mutable std::mutex m_queueMutex;
    };
}

#endif //EVENT_QUEUE_HPP