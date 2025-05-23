// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "MovingTargetBiasedSampler.h"

std::unique_ptr<IComponent> MovingTargetBiasedSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<MovingTargetBiasedSampler>(context.envSettings->boundaries, goalBias);
}

Keyframe MovingTargetBiasedSampler::sampleTarget(const Animation &target)
{
    std::vector<Keyframe> keyframes = target.getKeyframes();
    std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
    int randomIndex = distribution(gen);
    return keyframes[randomIndex];
}

Keyframe MovingTargetBiasedSampler::sampleRandom()
{
    return Keyframe(sampleRandomPose(), -1);
}

