//
// Created by arseniy on 15.1.25.
//

#include "TRRTsolverFactory.h"

std::shared_ptr<TRRTsolver> TRRTsolverFactory::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));
    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));

    TRRTsolverConfig solverConfig(
           goalBias,
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor,
           velocity
       );

    return std::make_shared<TRRTsolver>(solverConfig, context.envSettings);
}
