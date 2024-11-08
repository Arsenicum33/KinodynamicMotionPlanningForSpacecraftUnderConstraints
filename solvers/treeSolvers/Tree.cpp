//
// Created by arseniy on 8.11.24.
//

#include "Tree.h"

#include "../../collisionHandlers/RapidCollisionHandler.h"


const std::vector<std::shared_ptr<TreeNode>> & Tree::getNodes()
{
    return nodes;
}

std::shared_ptr<TreeNode> Tree::addNode(const Pose &pose, const std::shared_ptr<TreeNode> &parentNode)
{
    double distance = distanceMetric->getDistance(pose, parentNode->pose);
    double cost = parentNode->getCost() + distance;
    std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(pose, parentNode, cost);
    parentNode->children.push_back(newNode);
    nodes.push_back(newNode);
    return newNode;
}

void Tree::initializeTree(const Pose& startPosition)
{
    root = std::make_shared<TreeNode>(startPosition, nullptr, 0.0);
    nodes.reserve(100000);
    nodes.push_back(root);
}

void Tree::rewireTree(std::shared_ptr<TreeNode> newNode, std::vector<int> nearestNeighboursIndexes, std::shared_ptr<ICollisionHandler> collisionHandler)
{
    for (auto idx : nearestNeighboursIndexes)
    {
        auto& nearestNeighbour = nodes[idx];
        double distance = distanceMetric->getDistance(newNode->pose, nearestNeighbour->pose);
        if (nearestNeighbour->getCost() > newNode->getCost() + distance)
        {
            auto poses = PoseMath::interpolatePoses( nearestNeighbour->pose, newNode->pose,0.1,0.1);
            if (!collisionHandler->arePosesCollisionFree(poses))
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
