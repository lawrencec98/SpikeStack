#ifndef SPIKE_HPP
#define SPIKE_HPP


namespace spikestack
{
    namespace spike 
    {
        enum class Polarity {
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
            double occ_time; // The point at which the neuron exceeded v_threshold.
            double delivered_time; // This factors in synaptic delay.
        };


        typedef std::shared_ptr<Spike> Spike_sp;
        typedef std::shared_ptr<InputSpike> InputSpike_sp;
    
    } //namespace spike
} //namespace spikestack


#endif // SPIKE_HPP