//
// Created by arseniy on 8.11.24.
//

#ifndef TREE_H
#define TREE_H
#include <memory>

#include "TreeNode.h"
#include "../../../collisionHandlers/ICollisionHandler.h"
#include "../../../distanceMeasurement/IDistanceMetric.h"
#include "components/interpolators/IInterpolator.h"

template <typename PositionType>
class Tree
{
public:
    Tree(std::shared_ptr<IDistanceMetric> distanceMetric, std::shared_ptr<IInterpolator<PositionType>> interpolator,
        std::shared_ptr<ICollisionHandler<PositionType>> collisionHandler) :
            distanceMetric(distanceMetric), interpolator(interpolator), collisionHandler(collisionHandler) { nodes.clear(); }
    const std::vector<std::shared_ptr<TreeNode<PositionType>>>& getNodes();
    std::shared_ptr<TreeNode<PositionType>> addNode(const PositionType &pose, std::shared_ptr<TreeNode<PositionType>> &parentNode);
    void initializeTree(const PositionType& startPosition);
    void rewireTree(std::shared_ptr<TreeNode<PositionType>> newNode, std::vector<int> nearestNeighboursIndexes, std::shared_ptr<ICollisionHandler<PositionType>> handler);
private:
    std::vector<std::shared_ptr<TreeNode<PositionType>>> nodes;
    std::shared_ptr<TreeNode<PositionType>> root;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<IInterpolator<PositionType>> interpolator;
    std::shared_ptr<ICollisionHandler<PositionType>> collisionHandler;

};

template <typename PositionType>
const std::vector<std::shared_ptr<TreeNode<PositionType>>> & Tree<PositionType>::getNodes()
{
    return nodes;
}

template <typename PositionType>
std::shared_ptr<TreeNode<PositionType>> Tree<PositionType>::addNode(const PositionType &pose, std::shared_ptr<TreeNode<PositionType>> &parentNode)
{
    double distance = distanceMetric->getSpatialDistance(pose, parentNode->pose); //Might be changed to getTotalDistance when doing path optimization
    double cost = parentNode->getCost() + distance;
    std::shared_ptr<TreeNode<PositionType>> newNode = std::make_shared<TreeNode<PositionType>>(pose, parentNode, cost);
    parentNode->children.push_back(newNode);
    nodes.push_back(newNode);
    return newNode;
}

template <typename PositionType>
void Tree<PositionType>::initializeTree(const PositionType &startPosition)
{
    root = std::make_shared<TreeNode<PositionType>>(startPosition, nullptr, 0.0);
    nodes.reserve(100000);
    nodes.push_back(root);
}

template <typename PositionType>
void Tree<PositionType>::rewireTree(std::shared_ptr<TreeNode<PositionType>> newNode, std::vector<int> nearestNeighboursIndexes,
    std::shared_ptr<ICollisionHandler<PositionType>> handler)
{
    for (auto idx : nearestNeighboursIndexes)
    {
        auto& nearestNeighbour = nodes[idx];
        double distance = distanceMetric->getSpatialDistance(newNode->pose, nearestNeighbour->pose);
        if (nearestNeighbour->getCost() > newNode->getCost() + distance)
        {
            auto positions = interpolator->interpolate(nearestNeighbour->pose, newNode->pose);
            if (!handler->arePosesCollisionFree(positions))
                continue;
            auto& previousParentChildren = nearestNeighbour->parent->children;
            auto it = std::find(previousParentChildren.begin(), previousParentChildren.end(), nearestNeighbour);
            if (it != previousParentChildren.end())
            {
                previousParentChildren.erase(it);
            }
            nearestNeighbour->parent = newNode;
            nearestNeighbour->updateCost(newNode->getCost() + distance);
        }
    }
}




#endif //TREE_H
