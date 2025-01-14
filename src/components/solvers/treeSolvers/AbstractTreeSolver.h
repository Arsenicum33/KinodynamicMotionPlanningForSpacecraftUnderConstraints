//
// Created by arseniy on 22.10.24.
//

#ifndef PLANNINGABSTRACTTREESOLVER_H
#define PLANNINGABSTRACTTREESOLVER_H

#include "Tree.h"
#include "../AbstractSolver.h"
#include "TreeNode.h"
#include "../AbstractSolverTemplated.h"
#include "../../pathGenerator/IPathGenerator.h"

template <typename ConfigType>
class AbstractTreeSolver : public AbstractSolverTemplated<ConfigType>
{
protected:
    std::unique_ptr<Tree> tree;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<IPathGenerator> pathGenerator;

    AbstractTreeSolver(const ConfigType& config,  const EnvSettings& envSettings)
        : AbstractSolverTemplated<ConfigType>(config, envSettings)
    {
    }

public:
    void build() override {tree = std::make_unique<Tree>(distanceMetric);};
};



#endif //PLANNINGABSTRACTTREESOLVER_H
