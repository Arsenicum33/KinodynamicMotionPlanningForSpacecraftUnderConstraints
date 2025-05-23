// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.

#include "MovingTargetTerminationCondition.h"

#include "utils/AnimationUtils.h"

std::unique_ptr<IComponent> MovingTargetTerminationCondition::createComponent(const ComponentConfig &config,
                                                                              const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<MovingTargetTerminationCondition>(threshold);
}

void MovingTargetTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Keyframe, Animation>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<ITotalDistanceMetric<Keyframe>>(manager->getComponent(ComponentType::DistanceMetric));
}

double MovingTargetTerminationCondition::computeDistance(const Keyframe &currentPosition, const Animation &target)
{
    return distanceMetric->getSpatialDistance(currentPosition, AnimationUtils::extractKeyframeAtTime(&target, currentPosition.time));
}
