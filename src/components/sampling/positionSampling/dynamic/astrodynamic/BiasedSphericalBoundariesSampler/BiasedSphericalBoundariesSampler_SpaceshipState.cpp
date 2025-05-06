//
// Created by arseniy on 5.5.25.
//

#include "BiasedSphericalBoundariesSampler_SpaceshipState.h"

std::unique_ptr<IComponent> BiasedSphericalBoundariesSampler_SpaceshipState::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    auto keyframeSamplerComponent = BiasedSphericalBoundariesSampler::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<BiasedSphericalBoundariesSampler*>(keyframeSamplerComponent.get()))
    {
        keyframeSamplerComponent.release();
        std::unique_ptr<BiasedSphericalBoundariesSampler> keyframeSampler(castPtr);
        return std::make_unique<BiasedSphericalBoundariesSampler_SpaceshipState>(std::move(keyframeSampler));
    }
    spdlog::error("Error when creating BiasedSphericalBoundariesSampler_SpaceshipState. Provided BiasedSphericalBoundariesSampler is invalid");
    throw std::runtime_error("Error when creating BiasedSphericalBoundariesSampler_SpaceshipState. Provided BiasedSphericalBoundariesSampler is invalid");
}

SpaceshipState BiasedSphericalBoundariesSampler_SpaceshipState::sample(const CelestialBody &target)
{
    Keyframe sampleKeyframe = sampler->sample(target);
    return SpaceshipState(State(sampleKeyframe, {0.0,0.0,0.0}, {0.0,0.0,0.0}), FuelState(0.0,0.0));
}
