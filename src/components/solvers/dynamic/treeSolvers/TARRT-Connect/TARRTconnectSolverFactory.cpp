//
// Created by arseniy on 19.1.25.
//

#include "TARRTconnectSolverFactory.h"

std::unique_ptr<TARRTconnectSolver> TARRTconnectSolverFactory::createComponent(const ComponentConfig &config,
    const ReaderContext &context)
{
    const auto& configMap = config.config;


    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));
    double maxTime = std::any_cast<double>(configMap.at("maxTime"));
    double connectionThreshold = std::any_cast<double>(configMap.at("connectionThreshold"));

    TARRTconnectSolverConfig solverConfig(
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor,
           velocity,
           maxTime,
           connectionThreshold
       );

    return std::make_unique<TARRTconnectSolver>(solverConfig, context.envSettings);
}
