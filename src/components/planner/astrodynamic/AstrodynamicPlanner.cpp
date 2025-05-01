//
// Created by arseniy on 30.4.25.
//

#include "AstrodynamicPlanner.h"

std::unique_ptr<IComponent> AstrodynamicPlanner::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;

    double timeResolution = std::any_cast<double>(configMap.at("timeResolution"));

    return std::make_unique<AstrodynamicPlanner>(timeResolution);
}
