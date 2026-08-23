#ifndef I_NEURON_HPP
#define I_NEURON_HPP

#include <memory>
#include <vector>

#include "Spike.hpp"
#include "Synapse.hpp"
#include "Types.hpp"

namespace spikestack 
{
    
    
class INeuron
{
public:
    virtual ~INeuron() = default;
    virtual void PushSpike(spike::Spike spike, Time current_simtime) = 0;
    virtual void Fire(Time sim_time) = 0;

    virtual std::vector<SynapseId> GetPreSynapses() const = 0;
    virtual std::vector<SynapseId> GetPostSynapses() const = 0;
};


}//namespace spikestack


#endif // I_NEURON_HPP