//
// Created by arseniy on 8.11.24.
//

#include "TreeNode.h"

void TreeNode::updateCost(double cost)
{
    double costDifference = this->cost - cost;
    this->cost = cost;
    for (auto child : children)
    {
        child->updateCost(child->cost - costDifference);
    }
}
