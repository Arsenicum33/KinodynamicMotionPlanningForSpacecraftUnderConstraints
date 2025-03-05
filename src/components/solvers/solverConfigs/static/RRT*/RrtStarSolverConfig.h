//
// Created by arseniy on 23.10.24.
//

#ifndef RRTSTARSOLVERCONFIG_H
#define RRTSTARSOLVERCONFIG_H

#include "../../ARRTsolverConfig.h"

class RrtStarSolverConfig : public ARRTSolverConfig
{
public:

    RrtStarSolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor):
    ARRTSolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}
};



#endif //RRTSTARSOLVERCONFIG_H
