//
// Created by arseniy on 18.3.25.
//

#ifndef MOVINGTARGETBIASEDSAMPLER_H
#define MOVINGTARGETBIASEDSAMPLER_H
#include "../../ABiasedRandomSampler.h"


class MovingTargetBiasedSampler : public ABiasedRandomSampler<Keyframe, Animation>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    MovingTargetBiasedSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<Keyframe, Animation>(boundaries, goalBias) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::MovingTarget,
        Capability::DynamicEnv, Capability::KinodynamicEnv}; }

protected:
    Keyframe sampleTarget(const Animation &target) override;

    Keyframe sampleRandom() override;


};



#endif //MOVINGTARGETBIASEDSAMPLER_H
