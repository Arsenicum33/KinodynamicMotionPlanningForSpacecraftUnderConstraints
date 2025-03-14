//
// Created by arseniy on 28.10.24.
//

#include "BiasedRandomSampler.h"

std::unique_ptr<IComponent> BiasedRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<BiasedRandomSampler>(context.envSettings.boundaries, goalBias);
}

Pose BiasedRandomSampler::samplePose(Pose target)
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
        return target;
    return DefaultRandomSampler::samplePose(target);
}

void BiasedRandomSampler::validateConstructorParams()
{
    if (goalBias < 0.0 || goalBias > 1.0)
    {
        spdlog::error("Goal bias must be between 0.0 and 1.0");
        throw std::invalid_argument("goal bias must be between 0 and 1.");
    }
}
