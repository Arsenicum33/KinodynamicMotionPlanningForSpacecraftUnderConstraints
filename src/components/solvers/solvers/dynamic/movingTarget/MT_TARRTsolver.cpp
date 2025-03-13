//
// Created by arseniy on 7.3.25.
//

#include "MT_TARRTsolver.h"

#include "poses/dynamic/KeyframeMath.h"

//Use KD-tree to check if sampled pose is close enough to some of the frames of animation?
std::vector<Keyframe> MT_TARRTsolver::solve(const Pose &startPosition, const Animation &target)
{
    Keyframe startKeyframe = PoseMath::poseToKeyframe(startPosition, 1.0);
    tree->initializeTree(startKeyframe);
    nnSearch->addPoint(startKeyframe);
    double minDist = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;
    int outputIterationsPeriod = 10000;
    for (int i=0; i<config.maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, config.maxIterations);
        }

        Keyframe sampledKeyframe = sampler->samplePose(target); //Sampled keyframe might have time equal to -1

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledKeyframe);

        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];
        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledKeyframe, config.maxStepSize, distanceMetric);
        double newTime = nearestNeighbour->pose.time + distanceMetric->getSpatialDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
        Keyframe keyframeWithinStepSize = Keyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        Keyframe* collidingKeyframe = nullptr;
        if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe))
            continue;


        double newDist = distanceMetric->getSpatialDistance(keyframeWithinStepSize, target.getKeyframeAtTime(keyframeWithinStepSize.time));
        if (newDist < minDist)
        {
            minDist = newDist;
            spdlog::info("New min dist: {}, at time: {}", minDist, keyframeWithinStepSize.time);
        }
        tree->addNode(keyframeWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(keyframeWithinStepSize);
        if (terminationCondition->isTargetReached(keyframeWithinStepSize, target))
        {
            spdlog::info("Solution found");
            std::vector<Keyframe> path = pathGenerator->generatePath(tree->getNodes().back());
            return path;
        }


    }

    spdlog::warn("MT_TARRTsolver: solution not found");
    throw std::runtime_error("MT_TARRTsolver: solution not found");
}

void MT_TARRTsolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent("CollisionHandler"));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<Keyframe>>(manager->getComponent("NearestNeighbourSearch"));
    this->sampler = std::dynamic_pointer_cast<IKeyframeSampler<Animation>>(manager->getComponent("PoseSampler"));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Keyframe>>(manager->getComponent("PathGenerator"));
    this->terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<Keyframe, Animation>>(manager->getComponent("TerminationCondition"));
    ATreeSolver::resolveDependencies(config, manager);
}
