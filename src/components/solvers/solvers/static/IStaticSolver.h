//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTSOLVER_H
#define ABSTRACTSOLVER_H

#include <vector>
#include "components/IComponent.h"

class IStaticSolver
{
public:
    virtual ~IStaticSolver() = default;

    virtual std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) = 0;
};
#endif //ABSTRACTSOLVER_H
