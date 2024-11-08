//
// Created by arseniy on 12.10.24.
//

#include "RRTsolver.h"

#include "../../../poses/PoseMath.h"
#include <algorithm>

std::vector<Pose> RRTsolver::solve(const Pose& startPosition, const Pose& goalPosition)
{
    tree->initializeTree(startPosition);
    nnSearch->addPoint(startPosition);
    double minDistance = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;

    for (int i=0; i<config.maxIterations; i++)
    {
        Pose sampledPose = poseSampler->samplePose();

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledPose);


        std::shared_ptr<TreeNode> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);

        std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(nearestNeighbour->pose, poseWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        if (!collisionHandler->arePosesCollisionFree(posesOnPath))
            continue;

        tree->addNode(poseWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(poseWithinStepSize);

        double distanceToGoal = distanceMetric->getDistance(poseWithinStepSize, goalPosition);
        const double distanceToGoalThreshold = config.interpolationDistanceThreshold + config.interpolationRotationDistanceThreshold * config.rotationScalingFactor;
        if (distanceToGoal < distanceToGoalThreshold)
        {
            std::vector<Pose> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }
        if (distanceToGoal < minDistance)
            minDistance = distanceToGoal;

    }

    throw std::runtime_error("RRTsolver: No path found");
}


