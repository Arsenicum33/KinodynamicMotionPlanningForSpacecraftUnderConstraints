//
// Created by arseniy on 8.3.25.
//

#ifndef MT_TARRTSOLVERCONFIG_H
#define MT_TARRTSOLVERCONFIG_H
#include "components/solvers/solverConfigs/dynamic/TARRT/TARRTsolverConfig.h"

class MT_TARRTsolverConfig : public TARRTsolverConfig
{
public:
    MT_TARRTsolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold,
        double interpolationRotationDistanceThreshold, double rotationScalingFactor, double velocity)
        : TARRTsolverConfig(
            maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold,
            rotationScalingFactor, velocity){}
};

#endif //MT_TARRTSOLVERCONFIG_H
