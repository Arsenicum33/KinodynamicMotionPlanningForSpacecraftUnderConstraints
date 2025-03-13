//
// Created by arseniy on 10.3.25.
//

#ifndef MOVINGTARGETSAMPLER_H
#define MOVINGTARGETSAMPLER_H
#include <dto/ConfigurationSpaceBoundaries.h>
#include <poses/dynamic/Animation.h>
#include <spdlog/spdlog.h>

#include "components/capabilities/Capability.h"
#include "components/sampling/keyframe/IKeyframeSampler.h"
#include "components/sampling/pose/defaultRandom/DefaultRandomSampler.h"


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

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget};};

private:


    DefaultRandomSampler defaultRandomSampler;
    const double goalBias;
};



#endif //MOVINGTARGETSAMPLER_H
