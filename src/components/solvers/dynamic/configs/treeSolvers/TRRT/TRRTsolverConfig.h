//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVERCONFIG_H
#define TRRTSOLVERCONFIG_H
#include "components/solvers/dynamic/configs/treeSolvers/IDynamicTreeSolverConfig.h"

class TRRTsolverConfig : public IDynamicTreeSolverConfig
{
public:
    double initialTemperature;
    double velocity;
    TRRTsolverConfig(double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
       double rotationScalingFactor, double velocity,double initialTemperature=-1):
    initialTemperature(initialTemperature), velocity(velocity),
   IDynamicTreeSolverConfig(goalBias, maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}
};

#endif //TRRTSOLVERCONFIG_H
