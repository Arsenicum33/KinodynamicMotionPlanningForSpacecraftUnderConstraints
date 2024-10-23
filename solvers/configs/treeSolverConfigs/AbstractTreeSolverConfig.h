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

    static AbstractTreeSolverConfig fromJson(const Json::Value& json);
protected:
    AbstractTreeSolverConfig(ConfigurationSpaceBoundaries boundaries, double goalBias, int maxIterations, double maxStepSize, double interpolationDistanceThreshold):
    AbstractSolverConfig(boundaries), goalBias(goalBias), maxIterations(maxIterations), maxStepSize(maxStepSize), interpolationDistanceThreshold(interpolationDistanceThreshold) {}


};



#endif //ABSTRACTTREESOLVERCONFIG_H
