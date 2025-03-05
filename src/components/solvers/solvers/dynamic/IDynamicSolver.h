//
// Created by arseniy on 14.1.25.
//

#ifndef IDYNAMICSOLVER_H
#define IDYNAMICSOLVER_H
#include "components/solvers/ASolver.h"


class IDynamicSolver
{
public:
    virtual ~IDynamicSolver() = default;

    virtual std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) = 0;
};



#endif //IDYNAMICSOLVER_H
