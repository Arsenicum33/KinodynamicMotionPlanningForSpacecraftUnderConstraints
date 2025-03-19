//
// Created by arseniy on 18.3.25.
//

#include "DynamicRandomSampler.h"

std::unique_ptr<IComponent> DynamicRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<DynamicRandomSampler>(context.envSettings.boundaries);
}

Keyframe DynamicRandomSampler::sample(Pose target)
{
    return Keyframe(sampleRandomPose(), -1);
}
