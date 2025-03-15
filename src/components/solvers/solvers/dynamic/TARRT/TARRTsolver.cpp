//
// Created by arseniy on 14.1.25.
//

#include "TARRTsolver.h"

#include <spdlog/spdlog.h>

#include "poses/dynamic/KeyframeMath.h"

std::unique_ptr<IComponent> TARRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;
    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));

    return std::make_unique<TARRTsolver>(maxIterations, maxStepSize, velocity);
}

std::vector<Keyframe> TARRTsolver::solve(const Pose &startPosition, const Pose &goalPosition)
{
    Keyframe startKeyframe(startPosition, 1.0);
    tree->initializeTree(startKeyframe);
    nnSearch->addPoint(startPosition);
    double minDistance = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;
    int outputIterationsPeriod = 10000;
    for (int i=0; i<maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, maxIterations);
        }
        Pose sampledPose = poseSampler->samplePose(goalPosition);

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledPose);


        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];

        Pose poseWithinStepSize = interpolator->getIntermediatePosition(nearestNeighbour->pose, sampledPose, maxStepSize);
        double newTime = nearestNeighbour->pose.time + distanceMetric->getSpatialDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
        Keyframe keyframeWithinStepSize = PoseMath::poseToKeyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        Keyframe* collidingKeyframe = nullptr;
        if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe))
            continue;

        tree->addNode(keyframeWithinStepSize, nearestNeighbour);
        nnSearch->addPoint(keyframeWithinStepSize);

        double distanceToGoal = distanceMetric->getSpatialDistance(poseWithinStepSize, goalPosition);
        if (terminationCondition->isTargetReached(keyframeWithinStepSize, goalPosition))
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
    this->interpolator =  std::dynamic_pointer_cast<IKeyframeInterpolator>(manager->getComponent(ComponentType::Interpolator));
    this->terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<Pose, Pose>>(manager->getComponent(ComponentType::TerminationCondition));
}
