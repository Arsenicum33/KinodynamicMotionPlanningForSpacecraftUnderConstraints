//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVERCONFIG_H
#define TRRTSOLVERCONFIG_H

#include "../../ARRTsolverConfig.h"

class TARRTsolverConfig : public ARRTSolverConfig
{
public:
    double velocity;
    TARRTsolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
    double rotationScalingFactor, double velocity): velocity(velocity),
    ARRTSolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}
};

#endif //TRRTSOLVERCONFIG_H
