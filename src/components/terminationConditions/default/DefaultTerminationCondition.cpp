//
// Created by arseniy on 8.3.25.
//

#include "DefaultTerminationCondition.h"

std::unique_ptr<IComponent> DefaultTerminationCondition::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<DefaultTerminationCondition>(threshold);
}

bool DefaultTerminationCondition::isTargetReached(const Pose &currentPosition, const Pose& target) const
{
    double distance = distanceMetric->getSpatialDistance(currentPosition, target);
    return distance <= threshold;
}

void DefaultTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Pose, Pose>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}
