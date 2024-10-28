//
// Created by arseniy on 28.10.24.
//

#ifndef ABSTRACTNEARESTNEIGHBOURSEARCH_H
#define ABSTRACTNEARESTNEIGHBOURSEARCH_H
#include <memory>
#include "../solvers/treeSolvers/TreeNode.h"
#include "../poses/Pose.h"

class AbstractNearestNeighbourSearch
{
public:

    virtual ~AbstractNearestNeighbourSearch() = default;
    virtual std::shared_ptr<TreeNode> findNearestNeighbour(const Pose& pose, const std::vector<std::shared_ptr<TreeNode>>& nodes) = 0;
};

#endif //ABSTRACTNEARESTNEIGHBOURSEARCH_H
