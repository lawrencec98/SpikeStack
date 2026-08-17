#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <iostream>

#include "LifNeuron.hpp"

using namespace testing;


class Fixture_LifNeuron : public Test {
protected:
    void SetUp() override 
    {
        info.vrest = -0.7;
        info.vthreshold = -0.6;
        info.vreset = -0.5;
        info.vmin = -1.0;
        info.vmax = 1.0;
        info.vfiredSpike = 0.1;
        info.leakageRate = 0.2;
        info.refactoryPeriod = std::chrono::duration<double>(10.0);

        neuron = std::make_shared<LifNeuron>(info);
    }

    LifNeuronInfo info;
    std::shared_ptr<LifNeuron> neuron;
};

TEST_F(Fixture_LifNeuron, constructor)
{
    EXPECT_THAT(neuron->GetVoltageRest(), AllOf(Ge(-0.71), Le(-0.6999)));
    EXPECT_THAT(neuron->GetVoltageThreshold(), AllOf(Ge(-0.61), Le(-0.5999)));
    EXPECT_THAT(neuron->GetVoltageReset(), AllOf(Ge(-0.51), Le(-0.4999)));
    EXPECT_THAT(neuron->GetLeakageRate(), AllOf(Ge(0.0999), Le(0.21)));
    EXPECT_THAT(neuron->GetVoltageMin(), AllOf(Ge(-1.1), Le(-0.999)));
    EXPECT_THAT(neuron->GetVoltageMax(), AllOf(Ge(0.999), Le(1.1)));
    EXPECT_THAT(neuron->GetVoltageRefactoryPeriod(), AllOf(Ge(std::chrono::duration<double>(9.999)), Le(std::chrono::duration<double>(10.1))));
    EXPECT_THAT(neuron->GetVoltageInstantaneous(), AllOf(Ge(-0.71), Le(-0.6999))); //Should be eq to v_rest
}


TEST_F(Fixture_LifNeuron, PushSpike_positive)
{
    ASSERT_THAT(neuron->GetVoltageInstantaneous(), AllOf(Ge(-0.71), Le(-0.6999))); //Should be eq to v_rest

    // TODO

    spike::Spike spike{0, 0, spike::Polarity::positive, std::chrono::steady_clock::now()};
    neuron->PushSpike(spike);
}