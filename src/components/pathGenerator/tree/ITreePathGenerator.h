//
// Created by arseniy on 19.1.25.
//

#ifndef ITREEPATHGENERATOR_H
#define ITREEPATHGENERATOR_H
#include <components/pathGenerator/IPathGenerator.h>
#include <components/solvers/treeUtils/TreeNode.h>

template <typename PositionType>
class ITreePathGenerator  : public IPathGenerator
{
public:
    virtual std::vector<PositionType> generatePath(std::shared_ptr<const TreeNode<PositionType>> finalNode);
};

template<typename PositionType>
std::vector<PositionType> ITreePathGenerator<PositionType>::generatePath(std::shared_ptr<const TreeNode<PositionType>> finalNode)
{
    std::vector<PositionType> result;
    std::shared_ptr<const TreeNode<PositionType>> currentNode = finalNode;
    while (currentNode->parent != nullptr)
    {
        result.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    result.push_back(currentNode->pose);
    std::reverse(result.begin(), result.end());
    return result;
}


#endif //ITREEPATHGENERATOR_H
