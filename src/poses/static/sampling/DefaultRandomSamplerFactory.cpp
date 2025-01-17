//
// Created by arseniy on 14.1.25.
//

#include "DefaultRandomSamplerFactory.h"

#include "DefaultRandomSampler.h"

std::shared_ptr<IPoseSampler> DefaultRandomSamplerFactory::createComponent(const ComponentConfig &config,
                                                                           const ReaderContext &context)
{
    return std::make_shared<DefaultRandomSampler>(context.envSettings.boundaries);
}
