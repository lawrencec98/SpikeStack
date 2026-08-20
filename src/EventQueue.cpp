#include "EventQueue.hpp"


template<typename event>
spikestack::EventQueue<event>::EventQueue()
{
    
}


template<typename event>
spikestack::EventQueue<event>::~EventQueue()
{
    
}


template<typename event>
event spikestack::EventQueue<event>::PopEvent()
{
    std::lock_guard<std::mutex> lock(m_queueMutex);

    T ev = m_queue.front();
    
    m_queue.pop_front();

    return ev;
}


template<typename event>
void spikestack::EventQueue<event>::PushEvent(event event)
{
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_queue.push_back(event);
}