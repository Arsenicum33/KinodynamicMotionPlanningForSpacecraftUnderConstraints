// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


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

protected:
    Pose sampleTarget(const Pose &target) override;

    Pose sampleRandom() override;
};



#endif //STATICBIASEDRANDOMSAMPLER_H
