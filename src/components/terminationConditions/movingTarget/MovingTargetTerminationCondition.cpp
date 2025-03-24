//
// Created by arseniy on 8.3.25.
//

#include "MovingTargetTerminationCondition.h"

#include "components/interpolators/dynamic/IDynamicInterpolator.h"
#include "utils/AnimationUtils.h"

std::unique_ptr<IComponent> MovingTargetTerminationCondition::createComponent(const ComponentConfig &config,
                                                                              const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<MovingTargetTerminationCondition>(threshold);
}

bool MovingTargetTerminationCondition::isTargetReached(const Keyframe &currentPosition, const Animation &target)
{
    Keyframe targetAtCurrentTime = AnimationUtils::extractKeyframeAtTime(&target, currentPosition.time);
    double distance = distanceMetric->getSpatialDistance(currentPosition, targetAtCurrentTime);
    return distance <= threshold;
}

void MovingTargetTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Keyframe, Animation>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<ITotalDistanceMetric<Keyframe>>(manager->getComponent(ComponentType::DistanceMetric));
}
