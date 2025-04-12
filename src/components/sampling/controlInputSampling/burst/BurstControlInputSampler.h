//
// Created by arseniy on 7.4.25.
//

#ifndef BURSTCONTROLINPUTSAMPLER_H
#define BURSTCONTROLINPUTSAMPLER_H
#include <components/sampling/controlInputSampling/IControlInputSampler.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

template <typename StateType>
class BurstControlInputSampler : public IControlInputSampler<BurstControlInput, StateType>
{
public:
    BurstControlInputSampler(std::unique_ptr<StabilizingControlInputSampler> stabilizingControlInputSampler, double thrustBurstMaxDuration,
        double torqueBurstMaxDuration)
        : thrustBurstMaxDuration(thrustBurstMaxDuration), torqueBurstMaxDuration(torqueBurstMaxDuration),
        stabilizingControlInputSampler(std::move(stabilizingControlInputSampler)),
        thrustBurstDurationDist(0, thrustBurstMaxDuration), torqueBurstDurationDist(0, torqueBurstMaxDuration) {}


    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }

    BurstControlInput sample(const StateType &currentPosition) override;

    double getThrustBurstMaxDuration() const { return thrustBurstMaxDuration; }
    double getTorqueBurstMaxDuration() const { return torqueBurstMaxDuration; }
private:
    double thrustBurstMaxDuration;
    double torqueBurstMaxDuration;
    std::uniform_real_distribution<double> thrustBurstDurationDist;
    std::uniform_real_distribution<double> torqueBurstDurationDist;
    std::unique_ptr<StabilizingControlInputSampler> stabilizingControlInputSampler;
};

template<typename StateType>
BurstControlInput BurstControlInputSampler<StateType>::sample(const StateType &currentPosition)
{
    ControlInput controlInput = stabilizingControlInputSampler->sample(currentPosition);
    double thrustDuration = thrustBurstDurationDist(this->gen);
    double torqueDuration = torqueBurstDurationDist(this->gen);
    BurstControlInput burstControlInput(controlInput, thrustDuration, torqueDuration);
    return burstControlInput;
}


#endif //BURSTCONTROLINPUTSAMPLER_H
