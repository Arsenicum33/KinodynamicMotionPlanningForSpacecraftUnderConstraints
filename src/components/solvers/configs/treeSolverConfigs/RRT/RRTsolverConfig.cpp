//
// Created by arseniy on 23.10.24.
//

#include "RRTsolverConfig.h"


RRTsolverConfig RRTsolverConfig::fromJson(const Json::Value& json)
{
    AbstractTreeSolverConfig baseConfig = AbstractTreeSolverConfig::fromJson(json);

    return RRTsolverConfig(
        baseConfig.maxIterations,
        baseConfig.maxStepSize,
        baseConfig.interpolationDistanceThreshold,
        baseConfig.interpolationRotationDistanceThreshold,
        baseConfig.rotationScalingFactor
        );
}
