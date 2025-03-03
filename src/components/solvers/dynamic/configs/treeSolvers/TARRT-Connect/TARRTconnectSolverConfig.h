//
// Created by arseniy on 19.1.25.
//

#ifndef TARRTCONNECTSOLVERCONFIG_H
#define TARRTCONNECTSOLVERCONFIG_H
#include "components/solvers/dynamic/configs/treeSolvers/TARRT/TARRTsolverConfig.h"

class TARRTconnectSolverConfig : public TARRTsolverConfig
{
public:
    double maxTime;
    double connectionThreshold;
    TARRTconnectSolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
   double rotationScalingFactor, double velocity, double maxTime, double connectionThreshold): maxTime(maxTime), connectionThreshold(connectionThreshold),
    TARRTsolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor, velocity) {}
};

#endif //TARRTCONNECTSOLVERCONFIG_H
