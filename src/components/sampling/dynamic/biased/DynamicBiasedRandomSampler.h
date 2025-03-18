//
// Created by arseniy on 18.3.25.
//

#ifndef DYNAMICBIASEDRANDOMSAMPLER_H
#define DYNAMICBIASEDRANDOMSAMPLER_H
#include "components/sampling/ABiasedRandomSampler.h"


class DynamicBiasedRandomSampler : public ABiasedRandomSampler<Keyframe, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    DynamicBiasedRandomSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<Keyframe, Pose>(boundaries, goalBias) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

    Keyframe sample(Pose target) override;
};



#endif //DYNAMICBIASEDRANDOMSAMPLER_H
