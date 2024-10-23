//
// Created by arseniy on 12.10.24.
//

#include "RrtStarSolver.h"

std::vector<Pose> RrtStarSolver::solve(const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                                        const std::unique_ptr<RAPID_model> &agent,
                                        Pose startPosition,
                                        Pose goalPosition)
{
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(startPosition);
    nodes.push_back(root);


    return std::vector<Pose>();
}
