#ifndef SPIKE_HPP
#define SPIKE_HPP

#include <chrono>

namespace spike 
{
    enum Polarity {
        positive,
        negative
    };

    struct InputSpike
    {
        int x;
        int y;
        spike::Polarity polarity;
        std::chrono::steady_clock::time_point timestamp;
    };

    struct Spike
    {
        long int source_id;
        spike::Polarity polarity;
        std::chrono::steady_clock::time_point timestamp;
    };
}

#endif // SPIKE_HPP