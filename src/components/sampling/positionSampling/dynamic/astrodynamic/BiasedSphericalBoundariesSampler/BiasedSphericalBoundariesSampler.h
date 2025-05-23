// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef BIASEDSPHERICALBOUNDARIESSAMPLER_H
#define BIASEDSPHERICALBOUNDARIESSAMPLER_H

#include <random>
#include <components/sampling/positionSampling/IPositionSampler.h>

#include "dto/configurationSpaceSphericalBoundaries/ConfigurationSpaceSphericalBoundaries.h"
#include "dto/poses/astrodynamic/celestialBody/CelestialBody.h"


class BiasedSphericalBoundariesSampler : public IPositionSampler<Keyframe, CelestialBody>
{
public:
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);
    BiasedSphericalBoundariesSampler(ConfigurationSpaceSphericalBoundaries boundaries, double goalBias) :
        boundaries(boundaries), goalBias(goalBias), dis_phi(boundaries.phiMin, boundaries.phiMax),
        dis_theta(boundaries.thetaMin, boundaries.thetaMax), dis_r(boundaries.rMin, boundaries.rMax),
        dis_yaw(boundaries.yaw_min, boundaries.yaw_max), dis_pitch(boundaries.pitch_min, boundaries.pitch_max),
    dis_roll(boundaries.roll_min, boundaries.roll_max)
    {
        if (goalBias < 0.0 || goalBias > 1.0)
        {
            spdlog::error("Goal bias must be between 0.0 and 1.0");
            throw std::invalid_argument("goal bias must be between 0 and 1.");
    }   }

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv};}

    Keyframe sampleTarget(const CelestialBody & target);

    Keyframe sampleRandom();

    Keyframe sample(const CelestialBody &target) override;
private:
    ConfigurationSpaceSphericalBoundaries boundaries;
    double goalBias;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis_phi;
    std::uniform_real_distribution<double> dis_theta;
    std::uniform_real_distribution<double> dis_r;
    std::uniform_real_distribution<double> dis_yaw;
    std::uniform_real_distribution<double> dis_pitch;
    std::uniform_real_distribution<double> dis_roll;
};



#endif //BIASEDSPHERICALBOUNDARIESSAMPLER_H
