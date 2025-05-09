//
// Created by arseniy on 9.5.25.
//

#include "KinodynamicBiasedSampler.h"

std::unique_ptr<IComponent> KinodynamicBiasedSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));

    return std::make_unique<KinodynamicBiasedSampler>(context.envSettings->boundaries, goalBias);
}

State KinodynamicBiasedSampler::sampleTarget(const Animation &target)
{
    std::vector<Keyframe> keyframes = target.getKeyframes();
    std::uniform_int_distribution<size_t> distribution(0, keyframes.size() - 1);
    int randomIndex = distribution(gen);
    return State(keyframes[randomIndex], {0.0,0.0,0.0}, {0.0,0.0,0.0});
}

State KinodynamicBiasedSampler::sampleRandom()
{
    return State(Keyframe(sampleRandomPose(), -1), {0.0,0.0,0.0}, {0.0,0.0,0.0});
}
