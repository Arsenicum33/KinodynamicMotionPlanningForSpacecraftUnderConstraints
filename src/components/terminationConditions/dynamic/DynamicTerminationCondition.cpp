// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DynamicTerminationCondition.h"

std::unique_ptr<IComponent> DynamicTerminationCondition::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<DynamicTerminationCondition>(threshold);
}

void DynamicTerminationCondition::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ITerminationCondition<Keyframe, Pose>::resolveDependencies(config, manager);
    this->distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
}

double DynamicTerminationCondition::computeDistance(const Keyframe &currentPosition, const Pose &target)
{
    return distanceMetric->getSpatialDistance(currentPosition, target);
}
