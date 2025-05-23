// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "AstrodynamicTerminationCondition.h"

#include <utils/AnimationUtils.h>

std::unique_ptr<IComponent> AstrodynamicTerminationCondition::createComponent(const ComponentConfig &config,
                                                                              const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<AstrodynamicTerminationCondition>(threshold);
}

void AstrodynamicTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<SpaceshipState, CelestialBody>::resolveDependencies(config, manager);
    distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

double AstrodynamicTerminationCondition::computeDistance(const SpaceshipState &currentPosition,
    const CelestialBody &target)
{
    Keyframe targetAtCurrentTime = AnimationUtils::extractKeyframeAtTime(target.getAnimation(), currentPosition.time);
    return distanceMetric->getSpatialDistance(currentPosition, targetAtCurrentTime);
}

void AstrodynamicTerminationCondition::outputDebugInfo(const SpaceshipState &currentPosition)
{
    spdlog::info("Min dist to goal: {}\nTrans: {}, {}, {}\nVelocity: {}, {}, {}\nAngular velocity: {}, {}, {}\nFuel: main - {}, secondary - {}\nTime: {}", minDistToGoal, currentPosition.translation[0],
    currentPosition.translation[1], currentPosition.translation[2], currentPosition.velocity[0], currentPosition.velocity[1], currentPosition.velocity[2],
    currentPosition.angularVelocity[0], currentPosition.angularVelocity[1], currentPosition.angularVelocity[2], currentPosition.getFuel().getMainThrusterFuel(), currentPosition.getFuel().getRotationThrustersFuel(), currentPosition.time);
}
