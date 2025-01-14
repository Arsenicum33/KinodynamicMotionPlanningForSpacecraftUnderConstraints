//
// Created by arseniy on 14.1.25.
//

#include "RRTsolverFactory.h"

std::shared_ptr<AbstractSolver> RRTsolverFactory::createComponent(ComponentConfig &config, ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));
    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    RRTsolverConfig solverConfig(
           goalBias,
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor
       );

    return std::make_shared<RRTsolver>(solverConfig, context.envSettings);
}
