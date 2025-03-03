//
// Created by arseniy on 23.10.24.
//

#ifndef RRTSOLVERCONFIG_H
#define RRTSOLVERCONFIG_H
#include "../AbstractTreeSolverConfig.h"
#include <jsoncpp/json/json.h>

class RRTsolverConfig : public AbstractTreeSolverConfig
{
public:
    static RRTsolverConfig fromJson(const Json::Value& json);

    RRTsolverConfig(int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor):
    AbstractTreeSolverConfig(maxIterations, maxStepSize, interpolationDistanceThreshold, interpolationRotationDistanceThreshold, rotationScalingFactor) {}
};



#endif //RRTSOLVERCONFIG_H
