//
// Created by arseniy on 18.3.25.
//

#include "StaticRandomSampler.h"

std::unique_ptr<IComponent> StaticRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<StaticRandomSampler>(context.envSettings->boundaries);
}

Pose StaticRandomSampler::sample(Pose target)
{
    return sampleRandomPose();
}
