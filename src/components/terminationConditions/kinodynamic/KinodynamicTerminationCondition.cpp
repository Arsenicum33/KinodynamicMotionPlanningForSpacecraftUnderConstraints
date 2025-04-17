//
// Created by arseniy on 23.3.25.
//

#include "KinodynamicTerminationCondition.h"

#include "utils/AnimationUtils.h"

#define PRINT_THRESHOLD 0.99

std::unique_ptr<IComponent> KinodynamicTerminationCondition::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<KinodynamicTerminationCondition>(threshold);
}

bool KinodynamicTerminationCondition::isTargetReached(const State &currentPosition, const Animation &target)
{
    Keyframe targetAtCurrentTime = AnimationUtils::extractKeyframeAtTime(&target, currentPosition.time);
    double distance = distanceMetric->getSpatialDistance(currentPosition, targetAtCurrentTime);
    if (distance < minDistToGoal * PRINT_THRESHOLD)
    {
        minDistToGoal = distance;
        spdlog::debug("Min dist to goal: {}, Trans: {}, {}, {}, Time: {}", minDistToGoal, currentPosition.translation[0],
            currentPosition.translation[1], currentPosition.translation[2], currentPosition.time);
    }
    return distance <= threshold;
}

void KinodynamicTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<State, Animation>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}
