//
// Created by arseniy on 18.3.25.
//

#include "DynamicBiasedRandomSampler.h"

std::unique_ptr<IComponent> DynamicBiasedRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<DynamicBiasedRandomSampler>(context.envSettings.boundaries, goalBias);
}

Keyframe DynamicBiasedRandomSampler::sample(Pose target)
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
    {
        return Keyframe(target, -1);
    }
    return Keyframe(sampleRandomPose(), -1);
}
