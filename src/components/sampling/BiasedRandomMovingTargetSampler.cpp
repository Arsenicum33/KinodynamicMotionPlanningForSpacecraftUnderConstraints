//
// Created by arseniy on 10.3.25.
//

#include "BiasedRandomMovingTargetSampler.h"

#include <random>

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
