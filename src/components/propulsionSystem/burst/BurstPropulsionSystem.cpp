//
// Created by arseniy on 7.4.25.
//

#include "BurstPropulsionSystem.h"

std::unique_ptr<IComponent> BurstPropulsionSystem::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double maxTotalProfileDuration = std::any_cast<double>(configMap.at("maxTotalProfileDuration"));

    double burstMaxDuration = std::any_cast<double>(configMap.at("burstMaxDuration")); //TODO make it get data from PropulsionSystem's config

    return std::make_unique<BurstPropulsionSystem>(maxTotalProfileDuration, burstMaxDuration);
}

AccelerationProfile<BurstControlInput> BurstPropulsionSystem::generateAccelerationProfile(
    const BurstControlInput &controlInput)
{
    AccelerationProfile<BurstControlInput> accelerationProfile;
    double burstDuration = controlInput.getBurstDuration();
    accelerationProfile.addSegment(burstDuration, std::make_unique<BurstControlInput>(controlInput));
    double coastingDuration = burstDurationDist(gen) - burstDuration;
    BurstControlInput coastingControlInput(coastingDuration);
    accelerationProfile.addSegment(coastingDuration, std::make_unique<BurstControlInput>(coastingControlInput));
    return accelerationProfile;
}
