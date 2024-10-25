//
// Created by arseniy on 23.10.24.
//

#ifndef RRTSTARSOLVERCONFIG_H
#define RRTSTARSOLVERCONFIG_H
#include "../AbstractTreeSolverConfig.h"
#include "cassert"
#include <jsoncpp/json/json.h>

class RrtStarSolverConfig : public AbstractTreeSolverConfig
{
public:
    static RrtStarSolverConfig fromJson(const Json::Value& json);
protected:
    RrtStarSolverConfig(double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold):
    AbstractTreeSolverConfig(goalBias, maxIterations, maxStepSize, interpolationDistanceThreshold) {}
};



#endif //RRTSTARSOLVERCONFIG_H
