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
        double timestamp;
    };

    struct Spike
    {
        long int source_id;
        spike::Polarity polarity;
        double timestamp;
    };
}

#endif // SPIKE_HPP