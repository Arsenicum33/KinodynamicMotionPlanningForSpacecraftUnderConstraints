//
// Created by arseniy on 5.3.25.
//

#ifndef ARRTSOLVERCONFIG_H
#define ARRTSOLVERCONFIG_H

#include "ASolverConfig.h"

class ARRTSolverConfig : public ASolverConfig
{
public:
    int maxIterations;
    double maxStepSize;
    double interpolationDistanceThreshold;
    double interpolationRotationDistanceThreshold;

    ARRTSolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor): maxIterations(maxIterations), maxStepSize(maxStepSize), interpolationDistanceThreshold(interpolationDistanceThreshold),
        interpolationRotationDistanceThreshold(interpolationRotationDistanceThreshold), ASolverConfig(rotationScalingFactor){}
};

#endif //ARRTSOLVERCONFIG_H
