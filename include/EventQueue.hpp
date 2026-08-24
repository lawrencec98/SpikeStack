#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"

#include <memory>
#include <mutex>
#include <stdexcept>
#include <queue>


namespace spikestack
{

    
template<typename T>
class EventQueue
{
public:
    EventQueue();
    ~EventQueue();

    void PushEvent(T ev)
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_queue.push(ev);
    }
    
    T PopEvent()
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);

        if (!m_queue.empty())
        {
            T ev = m_queue.top();
            m_queue.pop();
            return ev;
        }
        else 
        {
            throw std::runtime_error("Error: EventQueue is empty");
        }
    }

private:
    std::priority_queue<T> m_queue;
    mutable std::mutex m_queueMutex;
};

    
}//namespace spikestack

#endif //EVENT_QUEUE_HPP