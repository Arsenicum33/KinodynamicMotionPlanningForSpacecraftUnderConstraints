//
// Created by arseniy on 7.4.25.
//

#ifndef BURSTCONTROLINPUTSAMPLER_H
#define BURSTCONTROLINPUTSAMPLER_H
#include <components/sampling/controlInputSampling/IControlInputSampler.h>
#include <dto/poses/dynamic/kinodynamic/state/State.h>

#include "components/sampling/controlInputSampling/rotationStabilizing/StabilizingControlInputSampler.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"


class BurstControlInputSampler : public IControlInputSampler<BurstControlInput, State>
{
public:
    BurstControlInputSampler(std::unique_ptr<StabilizingControlInputSampler> stabilizing_control_input_sampler, double burstMaxDuration)
        : burstMaxDuration(burstMaxDuration), stabilizingControlInputSampler(std::move(stabilizing_control_input_sampler)),
    burstDurationDist(0, burstMaxDuration) {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; }

    BurstControlInput sample(const State &currentPosition) override;

    double getBurstMaxDuration() const { return burstMaxDuration; }
private:
    double burstMaxDuration;
    std::uniform_real_distribution<double> burstDurationDist;
    std::unique_ptr<StabilizingControlInputSampler> stabilizingControlInputSampler;
};



#endif //BURSTCONTROLINPUTSAMPLER_H
