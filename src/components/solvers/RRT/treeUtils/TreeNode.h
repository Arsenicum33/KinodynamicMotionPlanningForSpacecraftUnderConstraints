// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef TREENODE_H
#define TREENODE_H

#include <memory>
#include <vector>

#include "ANode.h"

template <typename T>
class TreeNode : public ANode
{
public:
    T pose;
    std::weak_ptr<TreeNode<T>> parent;
    std::vector<std::shared_ptr<TreeNode<T>>> children;
    TreeNode(const T& pose, const std::shared_ptr<TreeNode<T>> &parentNode, double cost)
        : pose(pose), parent(parentNode), cost(cost)
    {

    }

    void updateCost(double cost)  {
        double costDifference = this->cost - cost;
        this->cost = cost;
        for (auto child : children)
        {
            child->updateCost(child->cost - costDifference);
        }
    };

    double getCost() const { return cost; }

    std::weak_ptr<ANode> getParent() override;

    std::vector<std::shared_ptr<ANode>> getChildren() override;

    const Pose * getStateRepresentation() const override;

private:
    double cost;

};

template<typename T>
std::weak_ptr<ANode> TreeNode<T>::getParent()
{
    return parent;
}

template<typename T>
std::vector<std::shared_ptr<ANode>> TreeNode<T>::getChildren()
{
    std::vector<std::shared_ptr<ANode>> result;
    for (auto child : children)
    {
        result.push_back(child);
    }
    return result;
}

template<typename T>
const Pose * TreeNode<T>::getStateRepresentation() const
{
    return &pose;
}


#endif //TREENODE_H
