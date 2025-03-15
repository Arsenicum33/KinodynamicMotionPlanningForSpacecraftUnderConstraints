//
// Created by arseniy on 7.3.25.
//

#include "MT_TARRTsolver.h"

#include "poses/dynamic/KeyframeMath.h"

std::unique_ptr<IComponent> MT_TARRTsolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;


    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));
    double velocity = std::any_cast<double>(configMap.at("velocity"));

    return std::make_unique<MT_TARRTsolver>(maxIterations, maxStepSize, velocity);
}

//Use KD-tree to check if sampled pose is close enough to some of the frames of animation?
std::vector<Keyframe> MT_TARRTsolver::solve(const Pose &startPosition, const Animation &target)
{
    Keyframe startKeyframe(startPosition, 1.0);
    tree->initializeTree(startKeyframe);
    nnSearch->addPoint(startKeyframe);
    double minDist = std::numeric_limits<double>::max();
    int nearestNeighbourIndex = -1;
    int outputIterationsPeriod = 10000;
    for (int i=0; i<maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, maxIterations);
        }

        Keyframe sampledKeyframe = sampler->samplePose(target); //Sampled keyframe might have time equal to -1

        nearestNeighbourIndex = nnSearch->findNearestNeighbourIndex(sampledKeyframe);

        std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = tree->getNodes()[nearestNeighbourIndex];
        Pose poseWithinStepSize = static_cast<Pose>(interpolator->getIntermediatePosition(nearestNeighbour->pose, sampledKeyframe, maxStepSize));
        double newTime = nearestNeighbour->pose.time + distanceMetric->getSpatialDistance(nearestNeighbour->pose, poseWithinStepSize)/velocity;
        Keyframe keyframeWithinStepSize = Keyframe(poseWithinStepSize, newTime);
        std::vector<Keyframe> keyframesOnPath = interpolator->interpolate(nearestNeighbour->pose, keyframeWithinStepSize);

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
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent(ComponentType::CollisionHandler));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<Keyframe>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    this->sampler = std::dynamic_pointer_cast<IKeyframeSampler<Animation>>(manager->getComponent(ComponentType::Sampler));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Keyframe>>(manager->getComponent(ComponentType::PathGenerator));
    this->terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<Keyframe, Animation>>(manager->getComponent(ComponentType::TerminationCondition));
    this->interpolator =  std::dynamic_pointer_cast<IKeyframeInterpolator>(manager->getComponent(ComponentType::Interpolator));
    ATreeSolver::resolveDependencies(config, manager);
}
