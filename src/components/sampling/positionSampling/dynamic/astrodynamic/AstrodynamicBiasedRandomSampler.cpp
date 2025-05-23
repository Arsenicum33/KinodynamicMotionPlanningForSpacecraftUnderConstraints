// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "AstrodynamicBiasedRandomSampler.h"

std::unique_ptr<IComponent> AstrodynamicBiasedRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<AstrodynamicBiasedRandomSampler>(context.envSettings->boundaries, goalBias);
}

Keyframe AstrodynamicBiasedRandomSampler::sampleTarget(const CelestialBody &target)
{
    std::vector<Keyframe> keyframes = target.getAnimation()->getKeyframes();
    std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
    int randomIndex = distribution(gen);
    return keyframes[randomIndex];
}

Keyframe AstrodynamicBiasedRandomSampler::sampleRandom()
{
    return Keyframe(sampleRandomPose(), -1);
}
