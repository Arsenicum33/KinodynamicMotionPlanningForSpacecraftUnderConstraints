//
// Created by arseniy on 12.10.24.
//

#include "RRTsolver.h"

#include <algorithm>
#include <spdlog/spdlog.h>

std::vector<Pose> RRTsolver::solve(const Pose& startPosition, const Pose& goalPosition)
{
    tree->initializeTree(startPosition);
    nnSearch->addPoint(startPosition);
    double minDistance = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;

    int outputIterationsPeriod = 10000;

    for (int i=0; i<config.maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, config.maxIterations);
        }
        Pose sampledPose = poseSampler->samplePose(goalPosition);

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledPose);


        std::shared_ptr<TreeNode<Pose>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);

        std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(nearestNeighbour->pose, poseWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);


        Pose* collisionResult = nullptr;
        if (!collisionHandler->arePosesCollisionFree(posesOnPath, collisionResult))
            continue;

        tree->addNode(poseWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(poseWithinStepSize);

        double distanceToGoal = distanceMetric->getSpatialDistance(poseWithinStepSize, goalPosition);
        const double distanceToGoalThreshold = config.interpolationDistanceThreshold + config.interpolationRotationDistanceThreshold * config.rotationScalingFactor;
        if (distanceToGoal < distanceToGoalThreshold)
        {
            spdlog::info("Solution found");
            std::vector<Pose> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }
        if (distanceToGoal < minDistance)
            minDistance = distanceToGoal;

    }

    spdlog::warn("RRTsolver: solution not found");
    throw std::runtime_error("RRTsolver: solution not found");
}

void RRTsolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ATreeSolver::resolveDependencies(config, manager);
    this->collisionHandler = std::dynamic_pointer_cast<ICollisionHandler>(manager->getComponent(ComponentType::CollisionHandler));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<Pose>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler<Pose>>(manager->getComponent(ComponentType::Sampler));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Pose>>(manager->getComponent(ComponentType::PathGenerator));
}

void RRTsolver::build()
{
    ATreeSolver::build();
}


