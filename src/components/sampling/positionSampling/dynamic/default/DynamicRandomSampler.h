//
// Created by arseniy on 18.3.25.
//

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

    Keyframe sample(Pose target) override;
};



#endif //DYNAMICRANDOMSAMPLER_H
