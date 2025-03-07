//
// Created by arseniy on 14.1.25.
//

#include "BiasedRandomSamplerFactory.h"

#include "BiasedRandomSampler.h"

std::unique_ptr<IPoseSampler> BiasedRandomSamplerFactory::createComponent(const ComponentConfig &config,
                                                                          const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    Pose goalPose = std::get<Pose>(context.envSettings.target);

    return std::make_unique<BiasedRandomSampler>(context.envSettings.boundaries, goalBias, goalPose);
}
