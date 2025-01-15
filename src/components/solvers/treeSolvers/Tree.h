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

template <typename T>
class Tree
{
public:
    Tree(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) { nodes.clear(); };
    const std::vector<std::shared_ptr<TreeNode<T>>>& getNodes();
    std::shared_ptr<TreeNode<T>> addNode(const T &pose, const std::shared_ptr<TreeNode<T>> &parentNode);
    void initializeTree(const T& startPosition);
    void rewireTree(std::shared_ptr<TreeNode<T>> newNode, std::vector<int> nearestNeighboursIndexes, std::shared_ptr<ICollisionHandler> handler);
private:
    std::vector<std::shared_ptr<TreeNode<T>>> nodes;
    std::shared_ptr<TreeNode<T>> root;
    std::shared_ptr<IDistanceMetric> distanceMetric;

};

template <typename T>
const std::vector<std::shared_ptr<TreeNode<T>>> & Tree<T>::getNodes()
{
    return nodes;
}

template<typename T>
std::shared_ptr<TreeNode<T>> Tree<T>::addNode(const T &pose, const std::shared_ptr<TreeNode<T>> &parentNode)
{
    double distance = distanceMetric->getDistance(pose, parentNode->pose);
    double cost = parentNode->getCost() + distance;
    std::shared_ptr<TreeNode<T>> newNode = std::make_shared<TreeNode<T>>(pose, parentNode, cost);
    parentNode->children.push_back(newNode);
    nodes.push_back(newNode);
    return newNode;
}

template<typename T>
void Tree<T>::initializeTree(const T &startPosition)
{
    root = std::make_shared<TreeNode<T>>(startPosition, nullptr, 0.0);
    nodes.reserve(100000);
    nodes.push_back(root);
}

template<typename T>
void Tree<T>::rewireTree(std::shared_ptr<TreeNode<T>> newNode, std::vector<int> nearestNeighboursIndexes,
    std::shared_ptr<ICollisionHandler> handler)
{
    for (auto idx : nearestNeighboursIndexes)
    {
        auto& nearestNeighbour = nodes[idx];
        double distance = distanceMetric->getDistance(newNode->pose, nearestNeighbour->pose);
        if (nearestNeighbour->getCost() > newNode->getCost() + distance)
        {
            auto poses = PoseMath::interpolatePoses( nearestNeighbour->pose, newNode->pose,0.1,0.1);
            if (!handler->arePosesCollisionFree(poses))
                continue;
            // throw std::runtime_error("Pose collision detected");
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
