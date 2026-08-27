#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"

#include <memory>
#include <mutex>
#include <stdexcept>
#include <queue>


namespace spikestack
{

struct EventComparator
{
    bool operator()(const std::shared_ptr<Event>& a, const std::shared_ptr<Event>& b) const
    {
        return a->occurence_timestamp > b->occurence_timestamp;
    }
};


// Made Comparator a template in case there are other types of events where
// we order by something other than occurence timestamp.
template<typename T, typename Comparator>
class EventQueue
{
public:
    EventQueue()
    :   m_queue(std::make_shared<std::priority_queue<T, std::vector<T>, Comparator>>())
    {
        // TODO: modify so that it knows what to order by.
    }

    ~EventQueue()
    {
        while(!m_queue->empty())
        {
            m_queue->pop();
        }
    }

    void PushEvent(T ev)
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_queue->push(ev);
    }
    
    T PopEvent()
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);

        if (!m_queue->empty())
        {
            T ev = m_queue->top();
            m_queue->pop();
            return ev;
        }
        else 
        {
            throw std::runtime_error("Error: EventQueue is empty");
        }
    }

private:
    std::shared_ptr<std::priority_queue<T, std::vector<T>, Comparator>> m_queue;
    mutable std::mutex m_queueMutex;
};

    
}//namespace spikestack

#endif //EVENT_QUEUE_HPP