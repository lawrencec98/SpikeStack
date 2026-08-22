#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"

#include <memory>
#include <mutex>
#include <queue>


namespace spikestack
{

    
template<typename event>
class EventQueue
{
public:
    EventQueue();
    ~EventQueue();
    void PushEvent(event ev);
    event PopEvent();

private:
    std::priority_queue<std::shared_ptr<event>> m_queue;
    mutable std::mutex m_queueMutex;
};

    
}//namespace spikestack

#endif //EVENT_QUEUE_HPP