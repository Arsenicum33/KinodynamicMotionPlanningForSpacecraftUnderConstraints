//
// Created by arseniy on 18.3.25.
//

#include "StaticBiasedRandomSampler.h"

std::unique_ptr<IComponent> StaticBiasedRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<StaticBiasedRandomSampler>(context.envSettings->boundaries, goalBias);
}

Pose StaticBiasedRandomSampler::sample(Pose target)
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
    {
        return target;
    }
    return sampleRandomPose();
}