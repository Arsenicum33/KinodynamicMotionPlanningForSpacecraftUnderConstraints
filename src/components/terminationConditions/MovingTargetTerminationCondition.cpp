//
// Created by arseniy on 8.3.25.
//

#include "MovingTargetTerminationCondition.h"

bool MovingTargetTerminationCondition::isTargetReached(const Keyframe &currentPosition, const Animation &target) const
{
    Keyframe targetAtCurrentTime = target.getKeyframeAtTime(currentPosition.time);
    double distance = distanceMetric->getDistance(currentPosition, targetAtCurrentTime);
    return distance <= threshold;
}

void MovingTargetTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent("DistanceMetric"));
    ITerminationCondition<Keyframe, Animation>::resolveDependencies(config, manager);
}
