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

    for (int i=0; i<config.maxIterations; i++)
    {
        Pose randomPose = sampleRandomPose(goalPosition);
        std::shared_ptr<TreeNode> nearestNeighbour = findNearestNeighbour(randomPose);

        Pose poseWithinStepSize = getPoseWithinStepSize(nearestNeighbour->pose, randomPose);

        if (!isPathCollisionFree(nearestNeighbour->pose, poseWithinStepSize, obstacles, agent))
            continue;

        auto newTreeNode = std::make_shared<TreeNode>(poseWithinStepSize, nearestNeighbour);
        nodes.push_back(newTreeNode);

        if (getDistance(newTreeNode->pose, goalPosition) < config.interpolationDistanceThreshold)
        {
            std::vector<Pose> path = generatePath(newTreeNode);
            return path;
        }

    }

    throw std::runtime_error("RRTsolver: No path found");
}

void RRTsolver::initializeTree(Pose& startPosition)
{
    root = std::make_shared<TreeNode>(startPosition);
    nodes.push_back(root);
}

Pose RRTsolver::sampleRandomPose(Pose& goalPosition)
{

    if (std::uniform_real_distribution(0.0, 1.0)(gen) < config.goalBias)
    {
        return goalPosition;
    }
    std::uniform_real_distribution<double> dis_x(boundaries.xMin, boundaries.xMax);
    std::uniform_real_distribution<double> dis_y(boundaries.yMin, boundaries.yMax);
    std::uniform_real_distribution<double> dis_z(boundaries.zMin, boundaries.zMax);
    std::array<double, 3> translation = {dis_x(gen), dis_y(gen), dis_z(gen)};

    std::uniform_real_distribution<double> dis_yaw(boundaries.yaw_min, boundaries.yaw_max);
    std::uniform_real_distribution<double> dis_pitch(boundaries.pitch_min, boundaries.pitch_max);
    std::uniform_real_distribution<double> dis_roll(boundaries.roll_min, boundaries.roll_max);
    std::array<double, 3> eulerAngles = {dis_yaw(gen), dis_pitch(gen), dis_roll(gen)};

    std::array<std::array<double, 3>, 3> rotation_matrix = PoseMath::eulerToRotationMatrix(eulerAngles);

    Pose pose(translation, rotation_matrix);
    return pose;
}

std::shared_ptr<TreeNode> RRTsolver::findNearestNeighbour(Pose& pose)
{
    double minDist = std::numeric_limits<double>::max();
    int minIndex = -1;
    for (int i = 0; i < nodes.size(); i++)
    {
        double distance = getDistance(nodes[i]->pose, pose);
        if (distance < minDist)
        {
            minDist = distance;
            minIndex = i;
        }
    }
    return nodes[minIndex];
}

Pose RRTsolver::getPoseWithinStepSize(const Pose &from, const Pose &to) const
{
    double distance = getDistance(from, to);
    if (distance <= config.maxStepSize) {
        return to;
    }

    double scale = config.maxStepSize / distance;

    std::array<double, 3> newTranslation;
    for (int i = 0; i < 3; ++i)
        {
        newTranslation[i] = from.translation[i] + scale * (to.translation[i] - from.translation[i]);
    }

    auto newRotation = from.rotation;

    return Pose(newTranslation, newRotation);
}

double RRTsolver::getDistance(const Pose &pose1, const Pose &pose2) const
{
    const std::array<double, 3>& t1 = pose1.translation;
    const std::array<double, 3>& t2 = pose2.translation;

    double dx = t2[0] - t1[0];
    double dy = t2[1] - t1[1];
    double dz = t2[2] - t1[2];

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

bool RRTsolver::isPathCollisionFree(const Pose &pose1, const Pose &pose2,
                                    const std::vector<std::unique_ptr<RAPID_model>> &obstacles,
                                    const std::unique_ptr<RAPID_model> &agent) const
{
    std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(pose1, pose2, config.interpolationDistanceThreshold);
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

