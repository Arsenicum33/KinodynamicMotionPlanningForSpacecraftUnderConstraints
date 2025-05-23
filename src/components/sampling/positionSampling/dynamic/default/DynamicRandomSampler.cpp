// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "DynamicRandomSampler.h"

std::unique_ptr<IComponent> DynamicRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<DynamicRandomSampler>(context.envSettings->boundaries);
}

Keyframe DynamicRandomSampler::sample(const Pose& target)
{
    return Keyframe(sampleRandomPose(), -1);
}
