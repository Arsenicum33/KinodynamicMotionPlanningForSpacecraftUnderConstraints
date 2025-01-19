//
// Created by arseniy on 14.1.25.
//

#ifndef TRRTSOLVERCONFIG_H
#define TRRTSOLVERCONFIG_H
#include "components/solvers/dynamic/configs/treeSolvers/IDynamicTreeSolverConfig.h"

class TARRTsolverConfig : public IDynamicTreeSolverConfig
{
public:
    double velocity;
    TARRTsolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
       double rotationScalingFactor, double velocity): velocity(velocity),
   IDynamicTreeSolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}
};

#endif //TRRTSOLVERCONFIG_H
