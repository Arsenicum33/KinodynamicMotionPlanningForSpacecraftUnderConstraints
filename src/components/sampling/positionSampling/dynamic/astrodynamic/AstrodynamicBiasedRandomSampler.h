// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ASTRODYNAMICBIASEDRANDOMSAMPLER_H
#define ASTRODYNAMICBIASEDRANDOMSAMPLER_H
#include <components/sampling/positionSampling/ABiasedRandomSampler.h>

#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"


class AstrodynamicBiasedRandomSampler : public ABiasedRandomSampler<Keyframe, CelestialBody>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    AstrodynamicBiasedRandomSampler(const ConfigurationSpaceBoundaries &boundaries, double goalBias)
        : ABiasedRandomSampler<Keyframe, CelestialBody>(boundaries, goalBias) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::MovingTarget,
        Capability::DynamicEnv, Capability::KinodynamicEnv}; }

protected:
    Keyframe sampleTarget(const CelestialBody &target) override;

    Keyframe sampleRandom() override;

};



#endif //ASTRODYNAMICBIASEDRANDOMSAMPLER_H
