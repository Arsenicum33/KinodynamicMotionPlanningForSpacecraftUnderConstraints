//
// Created by arseniy on 23.10.24.
//

#ifndef RRTSOLVERCONFIG_H
#define RRTSOLVERCONFIG_H
#include "components/solvers/solverConfigs/ARRTsolverConfig.h"
#include <jsoncpp/json/json.h>

class RRTsolverConfig : public ARRTSolverConfig
{
public:
    RRTsolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor):
    ARRTSolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}};



#endif //RRTSOLVERCONFIG_H
