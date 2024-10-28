//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTTREESOLVERCONFIG_H
#define ABSTRACTTREESOLVERCONFIG_H
#include "../AbstractSolverConfig.h"
#include "cassert"
#include <jsoncpp/json/json.h>

class AbstractTreeSolverConfig : public AbstractSolverConfig
{
public:
    double goalBias;
    int maxIterations;
    double maxStepSize;
    double interpolationDistanceThreshold;
    double interpolationRotationDistanceThreshold;

    static AbstractTreeSolverConfig fromJson(const Json::Value& json);
protected:
    AbstractTreeSolverConfig(double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold, double interpolationRotationDistanceThreshold,
        double rotationScalingFactor):
    goalBias(goalBias), maxIterations(maxIterations), maxStepSize(maxStepSize), interpolationDistanceThreshold(interpolationDistanceThreshold),
    interpolationRotationDistanceThreshold(interpolationRotationDistanceThreshold), AbstractSolverConfig(rotationScalingFactor){}


};



#endif //ABSTRACTTREESOLVERCONFIG_H
