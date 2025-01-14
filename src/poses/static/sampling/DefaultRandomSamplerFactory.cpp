//
// Created by arseniy on 14.1.25.
//

#include "DefaultRandomSamplerFactory.h"

#include "DefaultRandomSampler.h"

std::shared_ptr<IPoseSampler> DefaultRandomSamplerFactory::createComponent(ComponentConfig &config,
                                                                           ReaderContext &context)
{
    return std::make_shared<DefaultRandomSampler>(context.envSettings.boundaries);
}
