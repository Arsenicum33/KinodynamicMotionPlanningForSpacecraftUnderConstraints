//
// Created by arseniy on 5.5.25.
//

#include "AstrodynamicBiasedSphericalBoundariesSampler.h"

std::unique_ptr<IComponent> AstrodynamicBiasedSphericalBoundariesSampler::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    auto keyframeSamplerComponent = BiasedSphericalBoundariesSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<BiasedSphericalBoundariesSampler*>(keyframeSamplerComponent.get()))
    {
        keyframeSamplerComponent.release();
        std::unique_ptr<BiasedSphericalBoundariesSampler> keyframeSampler(castPtr);
        return std::make_unique<AstrodynamicBiasedSphericalBoundariesSampler>(std::move(keyframeSampler));
    }
    spdlog::error("Error when creating AstrodynamicBiasedSphericalBoundariesSampler. Provided BiasedSphericalBoundariesSampler is invalid");
    throw std::runtime_error("Error when creating AstrodynamicBiasedSphericalBoundariesSampler. Provided BiasedSphericalBoundariesSampler is invalid");
}

SpaceshipState AstrodynamicBiasedSphericalBoundariesSampler::sample(const CelestialBody &target)
{
    Keyframe sampleKeyframe = sampler->sample(target);
    return SpaceshipState(State(sampleKeyframe, {0.0,0.0,0.0}, {0.0,0.0,0.0}), FuelState(0.0,0.0));
}
