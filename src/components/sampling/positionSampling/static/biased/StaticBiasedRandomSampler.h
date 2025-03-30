//
// Created by arseniy on 18.3.25.
//

#ifndef STATICBIASEDRANDOMSAMPLER_H
#define STATICBIASEDRANDOMSAMPLER_H
#include "../../ABiasedRandomSampler.h"


class StaticBiasedRandomSampler : public ABiasedRandomSampler<Pose, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    StaticBiasedRandomSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<Pose, Pose>(boundaries, goalBias) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::StaticEnv}; }

    Pose sample(Pose target) override;
};



#endif //STATICBIASEDRANDOMSAMPLER_H
