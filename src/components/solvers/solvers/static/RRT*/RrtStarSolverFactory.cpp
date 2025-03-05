//
// Created by arseniy on 14.1.25.
//

#include "RrtStarSolverFactory.h"
#include "RrtStarSolver.h"

std::unique_ptr<RrtStarSolver> RrtStarSolverFactory::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    RrtStarSolverConfig solverConfig(
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor
       );

    return std::make_unique<RrtStarSolver>(solverConfig, context.envSettings);
}
