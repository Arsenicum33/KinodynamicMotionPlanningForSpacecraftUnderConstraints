//
// Created by arseniy on 15.1.25.
//

#include "TARRTsolverFactory.h"

std::shared_ptr<TARRTsolver> TARRTsolverFactory::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;


    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));

    TRRTsolverConfig solverConfig(
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor,
           velocity
       );

    return std::make_shared<TARRTsolver>(solverConfig, context.envSettings);
}
