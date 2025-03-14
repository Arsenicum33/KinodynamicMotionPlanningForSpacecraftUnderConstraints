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
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    BiasedRandomMovingTargetSampler(ConfigurationSpaceBoundaries boundaries, double goalBias) :
        defaultRandomSampler(boundaries), goalBias(goalBias) { validateConstructorParams(); }

    Keyframe samplePose(Animation target) override;

    CapabilitySet getCapabilities() const override { return CapabilitySet {Capability::StaticEnv, Capability::DynamicEnv, Capability::MovingTarget};};
private:
    DefaultRandomSampler defaultRandomSampler;
    const double goalBias;
    void validateConstructorParams();
};



#endif //MOVINGTARGETSAMPLER_H
