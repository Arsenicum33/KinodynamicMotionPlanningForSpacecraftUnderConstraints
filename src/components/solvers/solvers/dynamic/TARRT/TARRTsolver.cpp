//
// Created by arseniy on 14.1.25.
//

#include "TARRTsolver.h"

#include <spdlog/spdlog.h>

#include "poses/dynamic/KeyframeMath.h"

std::vector<Keyframe> TARRTsolver::solve(const Pose &startPosition, const Pose &goalPosition)
{
    Keyframe startKeyframe = PoseMath::poseToKeyframe(startPosition, 1.0);
    tree->initializeTree(startKeyframe);
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


        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);
        double newTime = nearestNeighbour->pose.time + distanceMetric->getSpatialDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
        Keyframe keyframeWithinStepSize = PoseMath::poseToKeyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        Keyframe* collidingKeyframe = nullptr;
        if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe))
            continue;

        tree->addNode(keyframeWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(keyframeWithinStepSize);

        double distanceToGoal = distanceMetric->getSpatialDistance(poseWithinStepSize, goalPosition);
        const double distanceToGoalThreshold = config.interpolationDistanceThreshold + config.interpolationRotationDistanceThreshold * config.rotationScalingFactor;
        if (distanceToGoal < distanceToGoalThreshold)
        {
            spdlog::info("Solution found");
            std::vector<Keyframe> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }
        if (distanceToGoal < minDistance)
            minDistance = distanceToGoal;

    }

    spdlog::warn("TARRTsolver: solution not found");
    throw std::runtime_error("TARRTsolver: solution not found");
}

void TARRTsolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ATreeSolver::resolveDependencies(config, manager);
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent(ComponentType::CollisionHandler));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<Pose>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler<Pose>>(manager->getComponent(ComponentType::Sampler));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Keyframe>>(manager->getComponent(ComponentType::PathGenerator));
}
