//
// Created by arseniy on 23.3.25.
//

#include "KinodynamicTerminationCondition.h"

#include "utils/AnimationUtils.h"



std::unique_ptr<IComponent> KinodynamicTerminationCondition::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<KinodynamicTerminationCondition>(threshold);
}



void KinodynamicTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<State, Animation>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

double KinodynamicTerminationCondition::computeDistance(const State &currentPosition, const Animation &target)
{
    return distanceMetric->getSpatialDistance(currentPosition, AnimationUtils::extractKeyframeAtTime(&target, currentPosition.time));
}
