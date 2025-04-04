//
// Created by arseniy on 18.3.25.
//

#include "MovingTargetBiasedSampler.h"

std::unique_ptr<IComponent> MovingTargetBiasedSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<MovingTargetBiasedSampler>(context.envSettings->boundaries, goalBias);
}

Keyframe MovingTargetBiasedSampler::sample(Animation target)
{
    if (std::generate_canonical<double, 10>(gen) < goalBias)
    {
        std::vector<Keyframe> keyframes = target.getKeyframes();
        std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
        int randomIndex = distribution(gen);
        return keyframes[randomIndex];
    }
    Pose sampledPose = sampleRandomPose();
    return Keyframe(sampledPose, -1);
}
