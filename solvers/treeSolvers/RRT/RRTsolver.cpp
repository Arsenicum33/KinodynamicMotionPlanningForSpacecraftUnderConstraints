//
// Created by arseniy on 12.10.24.
//

#include "RRTsolver.h"

#include "../../../poses/PoseMath.h"
#include <algorithm>

std::vector<Pose> RRTsolver::solve(const Pose& startPosition, const Pose& goalPosition)
{
    initializeTree(startPosition);
    double minDistance = std::numeric_limits<double>::max();


    for (int i=0; i<config.maxIterations; i++)
    {
        Pose sampledPose = poseSampler->samplePose();

        std::shared_ptr<TreeNode> nearestNeighbour = nnSearch->findNearestNeighbour(sampledPose, nodes);

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);

        std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(nearestNeighbour->pose, poseWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        if (!collisionHandler->arePosesCollisionFree(posesOnPath))
            continue;


        auto newTreeNode = std::make_shared<TreeNode>(poseWithinStepSize, nearestNeighbour);
        nodes.push_back(newTreeNode);

        double distanceToGoal = distanceMetric->getDistance(newTreeNode->pose, goalPosition);
        const double distanceToGoalThreshold = config.interpolationDistanceThreshold + config.interpolationRotationDistanceThreshold * config.rotationScalingFactor;
        if (distanceToGoal < distanceToGoalThreshold)
        {
            std::vector<Pose> path = generatePath(newTreeNode);
            return path;
        }
        if (distanceToGoal < minDistance)
            minDistance = distanceToGoal;

    }

    throw std::runtime_error("RRTsolver: No path found");
}

void RRTsolver::initializeTree(const Pose& startPosition)
{
    root = std::make_shared<TreeNode>(startPosition);
    nodes.push_back(root);
}


std::vector<Pose> RRTsolver::generatePath(std::shared_ptr<TreeNode> goalNode)
{
    std::vector<Pose> path;
    std::shared_ptr<TreeNode> currentNode = goalNode;
    while (currentNode->parent != nullptr)
    {
        path.push_back(currentNode->pose);
        currentNode = currentNode->parent;
    }
    path.push_back(currentNode->pose);
    std::reverse(path.begin(), path.end());
    return path;
}

