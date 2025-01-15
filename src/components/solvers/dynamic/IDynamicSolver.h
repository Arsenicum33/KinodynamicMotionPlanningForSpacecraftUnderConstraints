//
// Created by arseniy on 14.1.25.
//

#ifndef IDYNAMICSOLVER_H
#define IDYNAMICSOLVER_H
#include "components/solvers/ISolver.h"


class IDynamicSolver : public ISolver
{
public:
    virtual std::vector<Keyframe> solve(const Pose& startPosition, const Pose& goalPosition) = 0;
    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::DynamicEnv}; }
};



#endif //IDYNAMICSOLVER_H
