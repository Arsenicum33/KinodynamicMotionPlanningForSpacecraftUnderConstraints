// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef BIASEDSPHERICALBOUNDARIESSAMPLER_SPACESHIPSTATE_H
#define BIASEDSPHERICALBOUNDARIESSAMPLER_SPACESHIPSTATE_H
#include <components/sampling/positionSampling/IPositionSampler.h>

#include "BiasedSphericalBoundariesSampler.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"
#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicBiasedSphericalBoundariesSampler : public IPositionSampler<SpaceshipState, CelestialBody>
{
public:
    explicit AstrodynamicBiasedSphericalBoundariesSampler(
         std::unique_ptr<BiasedSphericalBoundariesSampler> sampler)
        : sampler(std::move(sampler))
    {}

    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv}; };

    SpaceshipState sample(const CelestialBody &target) override;

private:
    std::unique_ptr<BiasedSphericalBoundariesSampler> sampler;
};



#endif //BIASEDSPHERICALBOUNDARIESSAMPLER_SPACESHIPSTATE_H
