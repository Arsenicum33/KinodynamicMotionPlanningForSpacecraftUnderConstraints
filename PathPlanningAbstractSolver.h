//
// Created by arseniy on 12.10.24.
//

#ifndef PATHPLANNINGABSTRACTSOLVER_H
#define PATHPLANNINGABSTRACTSOLVER_H
#include <memory>
#include <RAPID.H>

#include "Pose.h"
#include <vector>


class PathPlanningAbstractSolver
{
public:
    virtual ~PathPlanningAbstractSolver() = default;

private:
    virtual std::vector<Pose>& solve(const std::vector<std::unique_ptr<RAPID_model>>& obstacles,
                                     const std::unique_ptr<RAPID_model>& agent,
                                     Pose startPosition,
                                     Pose goalPosition) = 0;
};



#endif //PATHPLANNINGABSTRACTSOLVER_H
