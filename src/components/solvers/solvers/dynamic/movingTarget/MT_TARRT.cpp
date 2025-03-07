//
// Created by arseniy on 7.3.25.
//

#include "MT_TARRT.h"

#include "poses/dynamic/KeyframeMath.h"

//Use KD-tree to check if sampled pose is close enough to some of the frames of animation?
std::vector<Keyframe> MT_TARRT::solve(const Pose &startPosition, const Animation &target)
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
        Pose sampledPose = poseSampler->samplePose();

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledPose);


        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);
        double newTime = nearestNeighbour->pose.time + distanceMetric->getDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
        Keyframe keyframeWithinStepSize = PoseMath::poseToKeyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        Keyframe* collidingKeyframe = nullptr;
        if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe))
            continue;

        tree->addNode(keyframeWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(keyframeWithinStepSize);

        double distanceToGoal = distanceMetric->getDistance(poseWithinStepSize, goalPosition);
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
