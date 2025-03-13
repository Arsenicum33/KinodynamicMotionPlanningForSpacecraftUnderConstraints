//
// Created by arseniy on 8.11.24.
//

#ifndef TREE_H
#define TREE_H
#include <memory>

#include "TreeNode.h"
#include "../../collisionHandlers/ICollisionHandler.h"
#include "../../distanceMeasurement/IDistanceMetric.h"
#include "../../../poses/static/PoseMath.h"

template <typename StoredType, typename DistanceMetricType>
class Tree
{
public:
    Tree(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) { nodes.clear(); };
    const std::vector<std::shared_ptr<TreeNode<StoredType>>>& getNodes();
    std::shared_ptr<TreeNode<StoredType>> addNode(const StoredType &pose, const std::shared_ptr<TreeNode<StoredType>> &parentNode);
    void initializeTree(const StoredType& startPosition);
    void rewireTree(std::shared_ptr<TreeNode<StoredType>> newNode, std::vector<int> nearestNeighboursIndexes, std::shared_ptr<ICollisionHandler> handler);
private:
    std::vector<std::shared_ptr<TreeNode<StoredType>>> nodes;
    std::shared_ptr<TreeNode<StoredType>> root;
    std::shared_ptr<IDistanceMetric> distanceMetric;

};

template <typename StoredType, typename DistanceMetricType>
const std::vector<std::shared_ptr<TreeNode<StoredType>>> & Tree<StoredType, DistanceMetricType>::getNodes()
{
    return nodes;
}

template <typename StoredType, typename DistanceMetricType>
std::shared_ptr<TreeNode<StoredType>> Tree<StoredType, DistanceMetricType>::addNode(const StoredType &pose, const std::shared_ptr<TreeNode<StoredType>> &parentNode)
{
    double distance = distanceMetric->getSpatialDistance(pose, parentNode->pose); //Might be changed to getTotalDistance when doing path optimization
    double cost = parentNode->getCost() + distance;
    std::shared_ptr<TreeNode<StoredType>> newNode = std::make_shared<TreeNode<StoredType>>(pose, parentNode, cost);
    parentNode->children.push_back(newNode);
    nodes.push_back(newNode);
    return newNode;
}

template <typename StoredType, typename DistanceMetricType>
void Tree<StoredType, DistanceMetricType>::initializeTree(const StoredType &startPosition)
{
    root = std::make_shared<TreeNode<StoredType>>(startPosition, nullptr, 0.0);
    nodes.reserve(100000);
    nodes.push_back(root);
}

template <typename StoredType, typename DistanceMetricType>
void Tree<StoredType, DistanceMetricType>::rewireTree(std::shared_ptr<TreeNode<StoredType>> newNode, std::vector<int> nearestNeighboursIndexes,
    std::shared_ptr<ICollisionHandler> handler)
{
    for (auto idx : nearestNeighboursIndexes)
    {
        auto& nearestNeighbour = nodes[idx];
        double distance = distanceMetric->getSpatialDistance(newNode->pose, nearestNeighbour->pose);
        if (nearestNeighbour->getCost() > newNode->getCost() + distance)
        {
            auto poses = PoseMath::interpolatePoses( nearestNeighbour->pose, newNode->pose,0.1,0.1);

            Pose* collidingPose = nullptr;
            if (!handler->arePosesCollisionFree(poses, collidingPose))
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
