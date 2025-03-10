//
// Created by arseniy on 10.3.25.
//

#include "BiasedRandomMovingTargetSamplerFactory.h"

std::unique_ptr<BiasedRandomMovingTargetSampler> BiasedRandomMovingTargetSamplerFactory::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<BiasedRandomMovingTargetSampler>(context.envSettings.boundaries, goalBias);
}
