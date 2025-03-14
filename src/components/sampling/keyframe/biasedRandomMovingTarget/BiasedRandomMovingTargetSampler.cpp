//
// Created by arseniy on 10.3.25.
//

#include "BiasedRandomMovingTargetSampler.h"

#include <random>

std::unique_ptr<IComponent> BiasedRandomMovingTargetSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<BiasedRandomMovingTargetSampler>(context.envSettings.boundaries, goalBias);
}

Keyframe BiasedRandomMovingTargetSampler::samplePose(Animation target)
{
    if (std::generate_canonical<double, 10>(defaultRandomSampler.getGenerator()) > goalBias)
    {
        Pose sampledPose = defaultRandomSampler.samplePose(static_cast<Pose>(target.getKeyframes().front()));
        return Keyframe(sampledPose, -1);
    }
    std::vector<Keyframe> keyframes = target.getKeyframes();
    std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
    int randomIndex = distribution(defaultRandomSampler.getGenerator());
    return  keyframes[randomIndex];
}

void BiasedRandomMovingTargetSampler::validateConstructorParams()
{
    if (goalBias < 0.0 || goalBias > 1.0)
    {
        spdlog::error("Goal bias must be between 0.0 and 1.0");
        throw std::invalid_argument("goal bias must be between 0 and 1.");
    }
}
