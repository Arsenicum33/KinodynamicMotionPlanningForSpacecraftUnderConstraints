//
// Created by arseniy on 15.1.25.
//

#include "DistanceTimeFunctionFactory.h"

std::unique_ptr<DistanceTimeFunction> DistanceTimeFunctionFactory::createComponent(ComponentConfig &config,
    ReaderContext &context)
{
    return std::make_unique<DistanceTimeFunction>(std::any_cast<double>(config.config.at("velocity")));
}
