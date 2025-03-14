//
// Created by arseniy on 14.3.25.
//

#ifndef ARRTSOLVER_H
#define ARRTSOLVER_H
#include "components/solvers/ASolver.h"
#include "components/solvers/treeUtils/ATreeSolver.h"

template <typename StoredPositionType, typename DistanceMetricPositionType>
class ARRTsolver : public ATreeSolver<StoredPositionType, DistanceMetricPositionType>
{
protected:
    ARRTsolver(int maxIterations, double maxStepSize) : maxIterations(maxIterations), maxStepSize(maxStepSize) {}
    int maxIterations;
    double maxStepSize;
};

#endif //ARRTSOLVER_H
