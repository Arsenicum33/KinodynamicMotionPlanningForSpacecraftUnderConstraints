//
// Created by arseniy on 8.11.24.
//

#ifndef IPATHGENERATOR_H
#define IPATHGENERATOR_H
#include <memory>
#include <vector>

#include "../poses/Pose.h"
#include "../solvers/treeSolvers/TreeNode.h"

class IPathGenerator
{
public:
    virtual ~IPathGenerator() = default;
    virtual std::vector<Pose> generatePath(std::shared_ptr<TreeNode> finalNode) = 0;
};

#endif //IPATHGENERATOR_H
