#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include <memory>

#include "INeuron.hpp"


namespace spikestack
{
    

class Synapse
{
public:
    std::shared_ptr<INeuron> getPreNeuron() const;
    std::shared_ptr<INeuron> getPostNeuron() const;
private:
    std::shared_ptr<INeuron> preNeuron;
    std::shared_ptr<INeuron> postNeuron;
};


} //namespace spikestack



#endif // SYNAPSE_HPP