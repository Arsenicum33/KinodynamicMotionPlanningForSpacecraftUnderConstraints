//
// Created by arseniy on 17.3.25.
//

#include "RRTsolver.h"

std::unique_ptr<IComponent> RRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    int outputPeriod = 10000;

    return std::make_unique<RRTsolver>(maxIterations, maxStepSize, outputPeriod);
}
