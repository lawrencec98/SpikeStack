# SpikeStack
An exploratory software stack for Neuromorphic computing

This project includes an implementation of a Leaky-Integrate-and-Fire Neuron, and a simple SNN simulator. The SNN simulator is an event-based simulator as opposed to a more common 'cycle-based' approach. Thus the simulator is potentially more efficient for sparse simulations, and less computationally expensive... at the cost of non determinism 😱 !

## How biological neurons work
### Main parts of a neuron:
**Dendrites**: These branch out and connect one neuron to other neurons, to receive chemical signals.

**Cell body**: Processes incoming spikes.

**Axom**: The long fibre that carries spikes away from the cell body.

**Synapse**: The microscopic gap between neurons where signals are exchanged.

![Neuron Diagram](readme_assets/neuron_diagram_small.jpg)

### 1 - Generating the Action potential 
When a neuron's membrane voltage crosses v_threshold, voltage-gated sodium channels in the cell membrane open - allowing an influx of sodium ions. This drives the membrane potential rapidly up from roughly -55mV to +40mV in less than a millisecond. Then sodium channel close and potassium channels open, driving voltage back down. Initially the voltage is driven below v_rest (to v_reset), but slowly returns to v_rest.

![Voltage graph when a Neuron fires](readme_assets/neuron_firing_voltage_graph.jpg)


### 2 - Arriving at the Synapse
When action potential reaches the presynaptic terminal:
* Voltage-gated calcium channels open, calcium channels rush into the terminal.
* The calcium triggers Neurotransmitters to be sent across the synaptic cleft.
* The neurotransmitters bind to receptors at the postsynaptic neuron, opening ion channels.
* The ion flow produces a postsynaptic potential (PSP) - a small voltage change in the postsynaptic neuron.
* Magnitude of the PSP is determined by synaptic weight: the amount of neurotransmitters sent, number of receptors, and how sensitive they are. And this is what we model as a weight matrix in computation.


### 3 - Spike Integration
A single PSP is typically not enough to fire a neuron - firing requires a summation of many spikes. Summation can happen in two ways. **Spatial summation** occurs when multiple synapses on the neuron receive a spike simultaneously - their PSPs add together. **Temporal summation** occurs when a single synapse fires repeatedly in quick succession - the PSPs overlap in time and accumulate.

PSP decays over time, with the voltage tending towards resting - the rate of this decay is characterized by the membrane time constant tau (τ). Two spikes must arrive within one time constant in order to temporally accumulate. The "leaky" in Leaky-Integrate-and-Fire Neurons refer to this - neurons leak PSP in between spikes, and only fires if enough inputs arrive closely in time.

## Notes
### Topics to review
* LIF Variations
* The F-I curve
* Hebbian Learning
* Hopfield networks.
* STDP - Spike timing dependent plasticity
* Neuromorphic compilers

### TODO List
#### Neuromorphic implementation
* Move away from linear voltageLeaked calculations. Follow a proper model for it.
* Implement STDP
* Do we apply synaptic weight at the fire() or pushinput()? OR, do we implement a synapse class which sits in between two neurons. (CHOOSING PUSHINPUT FOR NOW)

#### Project infrastructure
* Look into making the unit tests dir its own cmake subdirectory, so that it can build on its own. And then have flag in main project cmake that determines whether we build tests or not.
* configuration file should hold min voltage, voltage of fired spike.
* Make sure to explicitly 'type' the std::chrono time units - i.e. std::milli
* Look into implementing a wrapper class for std::chrono::steady_clock so that we can control time.

# References
* https://neuromorphiccore.ai/