//
// Created by arseniy on 22.10.24.
//

#ifndef PLANNINGABSTRACTTREESOLVER_H
#define PLANNINGABSTRACTTREESOLVER_H

#include "Tree.h"
#include "../AbstractSolver.h"
#include "TreeNode.h"
#include "../AbstractSolverTemplated.h"

template <typename ConfigType>
class AbstractTreeSolver : public AbstractSolverTemplated<ConfigType>
{
protected:


    std::unique_ptr<Tree> tree;

    std::shared_ptr<IDistanceMetric> distanceMetric;

    AbstractTreeSolver(const ConfigType& config,  const EnvSettings& envSettings, std::shared_ptr<IDistanceMetric> distanceMetric)
        : AbstractSolverTemplated<ConfigType>(config, envSettings), tree(std::make_unique<Tree>(distanceMetric)), distanceMetric(distanceMetric)
    {
    }
};



#endif //PLANNINGABSTRACTTREESOLVER_H
