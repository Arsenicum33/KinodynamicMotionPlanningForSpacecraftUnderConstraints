//
// Created by arseniy on 23.10.24.
//

#ifndef ABSTRACTSOLVER_H
#define ABSTRACTSOLVER_H

#include "../poses/static/Pose.h"
#include <vector>
#include <memory>
#include "RAPID.H"
class AbstractSolver
{
public:

    virtual ~AbstractSolver() = default;
    virtual std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) = 0;
};
#endif //ABSTRACTSOLVER_H
