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
protected:
    RRTsolverConfig(ConfigurationSpaceBoundaries boundaries, double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold):
    AbstractTreeSolverConfig(boundaries, goalBias, maxIterations, maxStepSize, interpolationDistanceThreshold) {}
};



#endif //RRTSOLVERCONFIG_H
