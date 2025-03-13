//
// Created by arseniy on 14.1.25.
//

#include "BiasedRandomSamplerFactory.h"

#include "BiasedRandomSampler.h"

std::unique_ptr<IPoseSampler<Pose>> BiasedRandomSamplerFactory::createComponent(const ComponentConfig &config,
                                                                          const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<BiasedRandomSampler>(context.envSettings.boundaries, goalBias);
}
