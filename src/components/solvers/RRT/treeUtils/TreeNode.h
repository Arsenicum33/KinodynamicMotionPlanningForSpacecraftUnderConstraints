//
// Created by arseniy on 23.10.24.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <memory>

template <typename T>
class TreeNode
{
public:
    T pose;
    std::shared_ptr<TreeNode<T>> parent;
    std::vector<std::shared_ptr<TreeNode<T>>> children;
    TreeNode(const T& pose, const std::shared_ptr<TreeNode<T>> &parentNode, double cost)
        : pose(pose), parent(parentNode), cost(cost) {}

    void updateCost(double cost)  {
        double costDifference = this->cost - cost;
        this->cost = cost;
        for (auto child : children)
        {
            child->updateCost(child->cost - costDifference);
        }
    };

    double getCost() const { return cost; }
private:
    double cost;

};


#endif //TREENODE_H
