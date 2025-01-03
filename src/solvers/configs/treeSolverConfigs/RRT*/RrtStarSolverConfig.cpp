//
// Created by arseniy on 23.10.24.
//

#include "RrtStarSolverConfig.h"

RrtStarSolverConfig RrtStarSolverConfig::fromJson(const Json::Value& json)
{
    AbstractTreeSolverConfig baseConfig = AbstractTreeSolverConfig::fromJson(json);
    int maxNeighbours = json["maxNeighbours"].asInt();
    return RrtStarSolverConfig(
        baseConfig.goalBias,
        baseConfig.maxIterations,
        baseConfig.maxStepSize,
        baseConfig.interpolationDistanceThreshold,
        baseConfig.interpolationRotationDistanceThreshold,
        baseConfig.rotationScalingFactor,
        maxNeighbours
        );
}
