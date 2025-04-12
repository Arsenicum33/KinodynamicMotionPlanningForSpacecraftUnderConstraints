//
// Created by arseniy on 12.4.25.
//

#ifndef KINODYNAMICBURSTSAMPLER_H
#define KINODYNAMICBURSTSAMPLER_H
#include "components/sampling/controlInputSampling/burst/BurstControlInputSampler.h"


class KinodynamicBurstSampler : public BurstControlInputSampler<State>
{
public:
    KinodynamicBurstSampler(std::unique_ptr<StabilizingControlInputSampler> stabilizingControlInputSampler,
        double thrustBurstMaxDuration, double torqueBurstMaxDuration)
        : BurstControlInputSampler<State>(
            std::move(stabilizingControlInputSampler), thrustBurstMaxDuration, torqueBurstMaxDuration) {}

    std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::KinodynamicEnv}; }

};



#endif //KINODYNAMICBURSTSAMPLER_H
