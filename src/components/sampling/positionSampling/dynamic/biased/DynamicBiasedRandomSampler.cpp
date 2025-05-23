// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DynamicBiasedRandomSampler.h"

std::unique_ptr<IComponent> DynamicBiasedRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<DynamicBiasedRandomSampler>(context.envSettings->boundaries, goalBias);
}

Keyframe DynamicBiasedRandomSampler::sampleTarget(const Pose& target)
{
    return Keyframe(target, -1);
}

Keyframe DynamicBiasedRandomSampler::sampleRandom()
{
    return Keyframe(sampleRandomPose(), -1);
}
