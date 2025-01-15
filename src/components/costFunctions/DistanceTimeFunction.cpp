//
// Created by arseniy on 15.1.25.
//

#include "DistanceTimeFunction.h"

void DistanceTimeFunction::apply(const TreeNode<Keyframe> &nearestNode, TreeNode<Keyframe> &newNode)
{
    double prevTime = nearestNode.pose.time;
    double distance = distanceMetric->getDistance(nearestNode.pose, newNode.pose);
    double timeToTravel = distance/velocity;
    newNode.pose.time = prevTime + timeToTravel;
}

void DistanceTimeFunction::resolveDependencies(ComponentConfig &config, ComponentManager *manager)
{
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent("DistanceMetric"));
    ICostFunction<Keyframe>::resolveDependencies(config, manager);
}
