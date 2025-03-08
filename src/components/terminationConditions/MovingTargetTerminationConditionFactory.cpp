//
// Created by arseniy on 8.3.25.
//

#include "MovingTargetTerminationConditionFactory.h"

#include "MovingTargetTerminationCondition.h"

std::unique_ptr<ITerminationCondition<Keyframe, Animation>> MovingTargetTerminationConditionFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<MovingTargetTerminationCondition>(threshold);
}
