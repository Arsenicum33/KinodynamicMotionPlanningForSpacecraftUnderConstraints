//
// Created by arseniy on 12.10.24.
//

#ifndef RRTSTARSOLVER_H
#define RRTSTARSOLVER_H
#include "../AbstractTreeSolver.h"
#include "../../configs/treeSolverConfigs/RRT*/RrtStarSolverConfig.h"

class RrtStarSolver : public AbstractTreeSolver<RrtStarSolverConfig>
{
public:
    std::vector<Pose> solve(const Pose& startPosition, const Pose& goalPosition) override;
    RrtStarSolver(const RrtStarSolverConfig &config, const EnvSettings& envSettings) : AbstractTreeSolver(config, envSettings) {}

};



#endif //RRTSTARSOLVER_H
