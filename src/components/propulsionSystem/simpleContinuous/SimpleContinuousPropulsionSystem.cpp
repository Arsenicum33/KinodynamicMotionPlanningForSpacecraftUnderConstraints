//
// Created by arseniy on 7.4.25.
//

#include "SimpleContinuousPropulsionSystem.h"


std::unique_ptr<IComponent> SimpleContinuousPropulsionSystem::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double inputDuration = std::any_cast<double>(configMap.at("inputDuration"));

    return std::make_unique<SimpleContinuousPropulsionSystem>(inputDuration);
}

AccelerationProfile<ControlInput> SimpleContinuousPropulsionSystem::generateAccelerationProfile(
    const ControlInput &controlInput)
{
    AccelerationProfile<ControlInput> accelerationProfile;
    accelerationProfile.addSegment(this->inputDuration, std::make_unique<ControlInput>(controlInput));
    return accelerationProfile;
}
