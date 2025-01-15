//
// Created by arseniy on 14.1.25.
//

#ifndef IDYNAMICTREESOLVERCONFIG_H
#define IDYNAMICTREESOLVERCONFIG_H
#include "components/solvers/dynamic/configs/IDynamicSolverConfig.h"

class IDynamicTreeSolverConfig : public IDynamicSolverConfig
{
public:
    double goalBias;
    int maxIterations;
    double maxStepSize;
    double interpolationDistanceThreshold;
    double interpolationRotationDistanceThreshold;

    IDynamicTreeSolverConfig(double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
    double rotationScalingFactor):
goalBias(goalBias), maxIterations(maxIterations), maxStepSize(maxStepSize), interpolationDistanceThreshold(interpolationDistanceThreshold),
interpolationRotationDistanceThreshold(interpolationRotationDistanceThreshold), IDynamicSolverConfig(rotationScalingFactor){}
};

#endif //IDYNAMICTREESOLVERCONFIG_H
