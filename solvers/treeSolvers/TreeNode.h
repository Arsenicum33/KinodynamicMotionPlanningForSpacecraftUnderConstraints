//
// Created by arseniy on 23.10.24.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <memory>

#include "../../poses/Pose.h"

class TreeNode
{
public:
    Pose pose;
    std::shared_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;
    TreeNode(const Pose& pose, const std::shared_ptr<TreeNode> &parentNode, double cost)
        : pose(pose), parent(parentNode), cost(cost) {}
    void updateCost(double cost);
    double getCost() const { return cost; }
private:
    double cost;

};


#endif //TREENODE_H
