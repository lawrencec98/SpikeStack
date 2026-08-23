#ifndef I_NEURON_HPP
#define I_NEURON_HPP

#include <memory>
#include <vector>

#include "Spike.hpp"
#include "Synapse.hpp"

namespace spikestack 
{

    
class INeuron
{
public:
    virtual ~INeuron() = default;
    virtual void PushSpike(spike::Spike spike, Time current_simtime) = 0;
    virtual void Fire(Time sim_time) = 0;

    virtual std::vector<std::shared_ptr<Synapse>> GetPreSynapses() const = 0;
    virtual std::vector<std::shared_ptr<Synapse>> GetPostSynapses() const = 0;
};


}//namespace spikestack


#endif // I_NEURON_HPP