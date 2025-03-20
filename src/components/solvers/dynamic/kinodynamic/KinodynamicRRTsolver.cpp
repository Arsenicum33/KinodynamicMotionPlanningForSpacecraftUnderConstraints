//
// Created by arseniy on 20.3.25.
//

#include "KinodynamicRRTsolver.h"

std::unique_ptr<IComponent> KinodynamicRRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = static_cast<int>(std::any_cast<double>(configMap.at("maxIterations")));
    int controlInputSamples = static_cast<int>(std::any_cast<double>(configMap.at("controlInputSamples")));
    int outputPeriod = 10000;

    return std::make_unique<KinodynamicRRTsolver>(maxIterations, outputPeriod, controlInputSamples);
}