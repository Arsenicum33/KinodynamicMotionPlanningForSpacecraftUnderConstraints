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

        if (terminationCondition->isTargetReached(keyframeWithinStepSize, target))
        {
            spdlog::info("Solution found");
            std::vector<Keyframe> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }

    }

    spdlog::warn("TARRTsolver: solution not found");
    throw std::runtime_error("TARRTsolver: solution not found");
}

void MT_TARRT::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent("CollisionHandler"));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch>(manager->getComponent("NearestNeighbourSearch"));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler>(manager->getComponent("PoseSampler"));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Keyframe>>(manager->getComponent("PathGenerator"));
    this->terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<Keyframe, Animation>>(manager->getComponent("TerminationCondition"));
    ATreeSolver::resolveDependencies(config, manager);
}
