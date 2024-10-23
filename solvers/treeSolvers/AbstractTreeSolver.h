//
// Created by arseniy on 22.10.24.
//

#ifndef PLANNINGABSTRACTTREESOLVER_H
#define PLANNINGABSTRACTTREESOLVER_H

#include "../AbstractSolver.h"
#include "TreeNode.h"
#include "../AbstractSolverTemplated.h"

template <typename ConfigType>
class AbstractTreeSolver : public AbstractSolverTemplated<ConfigType>
{
protected:


    std::shared_ptr<TreeNode> root;
    std::vector<std::shared_ptr<TreeNode>> nodes;



    AbstractTreeSolver(const ConfigType& config)
        : AbstractSolverTemplated<ConfigType>(config) {}

};



#endif //PLANNINGABSTRACTTREESOLVER_H
