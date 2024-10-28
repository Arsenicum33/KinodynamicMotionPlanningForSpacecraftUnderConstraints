//
// Created by arseniy on 12.10.24.
//

#include "RRTsolver.h"

#include "../../../poses/PoseMath.h"
#include <algorithm>

std::vector<Pose> RRTsolver::solve(const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                                   const std::unique_ptr<RAPID_model> &agent,
                                   Pose startPosition,
                                   Pose goalPosition)
{
    initializeTree(startPosition);
    double minDistance = std::numeric_limits<double>::max();


    for (int i=0; i<config.maxIterations; i++)
    {
        Pose sampledPose = poseSampler->samplePose();

        std::shared_ptr<TreeNode> nearestNeighbour = nnSearch->findNearestNeighbour(sampledPose, nodes);

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);

        if (!isPathCollisionFree(nearestNeighbour->pose, poseWithinStepSize, obstacles, agent))
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

void RRTsolver::initializeTree(Pose& startPosition)
{
    root = std::make_shared<TreeNode>(startPosition);
    nodes.push_back(root);
}


bool RRTsolver::isPathCollisionFree(const Pose &pose1, const Pose &pose2,
                                    const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                                    const std::unique_ptr<RAPID_model> &agent) const
{
    std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(pose1, pose2, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);
    std::array<double, 3> zero_transaltion = {0, 0, 0};
    double zero_rotation[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    for (auto& pose : posesOnPath)
    {
        for (auto& obstacle : obstacles)
        {
            RAPID_Collide(pose.rotation, pose.translation.data(), agent.get(), zero_rotation, zero_transaltion.data(), obstacle.get());
            if (RAPID_num_contacts > 0)
                return false;
        }
    }
    return true;
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

