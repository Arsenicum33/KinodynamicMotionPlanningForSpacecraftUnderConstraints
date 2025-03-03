//
// Created by arseniy on 14.1.25.
//

#include "TRRTsolver.h"

#include "poses/dynamic/KeyframeMath.h"

std::vector<Keyframe> TRRTsolver::solve(const Pose &startPosition, const Pose &goalPosition)
{
    Keyframe startKeyframe = PoseMath::poseToKeyframe(startPosition, 1.0);
    tree->initializeTree(startKeyframe);
    nnSearch->addPoint(startPosition);
    double minDistance = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;

    for (int i=0; i<config.maxIterations; i++)
    {
        Pose sampledPose = poseSampler->samplePose();

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledPose);


        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);
        double newTime = nearestNeighbour->pose.time + distanceMetric->getDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
        Keyframe keyframeWithinStepSize = PoseMath::poseToKeyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath))
            continue;

        tree->addNode(keyframeWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(keyframeWithinStepSize);

        double distanceToGoal = distanceMetric->getDistance(poseWithinStepSize, goalPosition);
        const double distanceToGoalThreshold = config.interpolationDistanceThreshold + config.interpolationRotationDistanceThreshold * config.rotationScalingFactor;
        if (distanceToGoal < distanceToGoalThreshold)
        {
            std::vector<Keyframe> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }
        if (distanceToGoal < minDistance)
            minDistance = distanceToGoal;

    }

    throw std::runtime_error("TRRTsolver: No path found");
}

void TRRTsolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent("CollisionHandler"));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch>(manager->getComponent("NearestNeighbourSearch"));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler>(manager->getComponent("PoseSampler"));
    IDynamicTreeSolver<TRRTsolverConfig>::resolveDependencies(config, manager);
}
