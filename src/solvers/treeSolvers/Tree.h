//
// Created by arseniy on 8.11.24.
//

#ifndef TREE_H
#define TREE_H
#include <memory>

#include "TreeNode.h"
#include "../../collisionHandlers/ICollisionHandler.h"
#include "../../distanceMeasurement/IDistanceMetric.h"
#include "../../poses/static/PoseMath.h"

class Tree
{
public:
    Tree(std::shared_ptr<IDistanceMetric> distanceMetric) : distanceMetric(distanceMetric) { nodes.clear(); };
    const std::vector<std::shared_ptr<TreeNode>>& getNodes();
    std::shared_ptr<TreeNode> addNode(const Pose& pose, const std::shared_ptr<TreeNode> &parentNode);
    void initializeTree(const Pose& startPosition);
    void rewireTree(std::shared_ptr<TreeNode> newNode, std::vector<int> nearestNeighboursIndexes, std::shared_ptr<ICollisionHandler> handler);
private:
    std::vector<std::shared_ptr<TreeNode>> nodes;
    std::shared_ptr<TreeNode> root;
    std::shared_ptr<IDistanceMetric> distanceMetric;
};



#endif //TREE_H
