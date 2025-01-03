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
    int maxNeighbours;
    static RrtStarSolverConfig fromJson(const Json::Value& json);
protected:
    RrtStarSolverConfig(double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor, int maxNeighbours):
    AbstractTreeSolverConfig(goalBias, maxIterations, maxStepSize, interpolationDistanceThreshold,interpolationRotationDistanceThreshold, rotationScalingFactor),
    maxNeighbours(maxNeighbours){}
};



#endif //RRTSTARSOLVERCONFIG_H
