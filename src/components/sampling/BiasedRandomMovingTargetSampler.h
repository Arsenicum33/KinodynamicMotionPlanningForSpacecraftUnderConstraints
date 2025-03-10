//
// Created by arseniy on 10.3.25.
//

#ifndef MOVINGTARGETSAMPLER_H
#define MOVINGTARGETSAMPLER_H
#include <spdlog/spdlog.h>

#include "DefaultRandomSampler.h"
#include "IKeyframeSampler.h"


class BiasedRandomMovingTargetSampler : public IKeyframeSampler<Animation>
{
public:
    BiasedRandomMovingTargetSampler(ConfigurationSpaceBoundaries boundaries, double goalBias) : goalBias(goalBias), defaultRandomSampler(boundaries)
    {
        if (goalBias < 0.0 || goalBias > 1.0)
        {
            spdlog::error("Goal bias must be between 0.0 and 1.0");
            throw std::invalid_argument("goal bias must be between 0 and 1.");
        }
    }
    Keyframe samplePose(Animation target) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::DynamicEnv, Capability::MovingTarget};};

private:


    DefaultRandomSampler defaultRandomSampler;
    const double goalBias;
};



#endif //MOVINGTARGETSAMPLER_H
