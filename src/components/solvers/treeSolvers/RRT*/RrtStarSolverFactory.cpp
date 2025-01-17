//
// Created by arseniy on 14.1.25.
//

#include "RrtStarSolverFactory.h"

#include <components/solvers/configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.h>

#include "RrtStarSolver.h"

std::shared_ptr<IStaticSolver> RrtStarSolverFactory::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double goalBias = std::any_cast<double>(configMap.at("goalBias"));
    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double interpolationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationDistanceThreshold"));
    double interpolationRotationDistanceThreshold = std::any_cast<double>(configMap.at("interpolationRotationDistanceThreshold"));
    double rotationScalingFactor = std::any_cast<double>(configMap.at("rotationScalingFactor"));

    RrtStarSolverConfig solverConfig(
           goalBias,
           maxIterations,
           maxStepSize,
           interpolationDistanceThreshold,
           interpolationRotationDistanceThreshold,
           rotationScalingFactor
       );

    return std::make_shared<RrtStarSolver>(solverConfig, context.envSettings);
}
