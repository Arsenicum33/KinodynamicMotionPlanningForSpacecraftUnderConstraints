//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include "PathPlanningAbstractSolver.h"


class RrtStarSolver : public PathPlanningAbstractSolver
{
public:
    std::vector<Pose> & solve(const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                              const std::unique_ptr<RAPID_model> &agent,
                              Pose startPosition,
                              Pose goalPosition) override;
};



#endif //RRTSTARSOLVER_H
