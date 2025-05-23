// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#include "StaticRandomSampler.h"

std::unique_ptr<IComponent> StaticRandomSampler::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    return std::make_unique<StaticRandomSampler>(context.envSettings->boundaries);
}

Pose StaticRandomSampler::sample(const Pose& target)
{
    return sampleRandomPose();
}
