//
// Created by arseniy on 8.3.25.
//

#include "DefaultTerminationConditionFactory.h"

#include "DefaultTerminationCondition.h"

std::unique_ptr<ITerminationCondition<Pose, Pose>> DefaultTerminationConditionFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double threshold = std::any_cast<double>(configMap.at("threshold"));

    return std::make_unique<DefaultTerminationCondition>(threshold);
}
