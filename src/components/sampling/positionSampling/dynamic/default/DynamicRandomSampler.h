// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef DYNAMICRANDOMSAMPLER_H
#define DYNAMICRANDOMSAMPLER_H
#include "../../ARandomSampler.h"


class DynamicRandomSampler : public ARandomSampler<Keyframe, Pose>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    explicit DynamicRandomSampler(const ConfigurationSpaceBoundaries &boundaries)
        : ARandomSampler<Keyframe, Pose>(boundaries) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv }; }

    Keyframe sample(const Pose& target) override;
};



#endif //DYNAMICRANDOMSAMPLER_H
