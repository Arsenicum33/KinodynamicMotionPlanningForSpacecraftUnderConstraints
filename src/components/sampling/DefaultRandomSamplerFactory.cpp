//
// Created by arseniy on 14.1.25.
//

#include "DefaultRandomSamplerFactory.h"

#include "DefaultRandomSampler.h"

std::unique_ptr<IPoseSampler<Pose>> DefaultRandomSamplerFactory::createComponent(const ComponentConfig &config,
                                                                           const ReaderContext &context)
{
    return std::make_unique<DefaultRandomSampler>(context.envSettings.boundaries);
}
