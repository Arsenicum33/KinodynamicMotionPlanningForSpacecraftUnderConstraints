//
// Created by arseniy on 19.1.25.
//

#include "TARRTconnectSolver.h"

#include <spdlog/spdlog.h>

#include "poses/dynamic/KeyframeMath.h"

std::vector<Keyframe> TARRTconnectSolver::solve(const Pose &startPosition, const Pose &goalPosition)
{
    Keyframe startKeyframe = PoseMath::poseToKeyframe(startPosition, 1.0);
    Keyframe endKeyframe = PoseMath::poseToKeyframe(goalPosition, config.maxTime);
    tree->initializeTree(startKeyframe);
    goalTree->initializeTree(endKeyframe);
    nnSearch->addPoint(startPosition);
    goalNNsearch->addPoint(goalPosition);

    int outputIterationsPeriod = 10000;
    for (int i=0; i<config.maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, config.maxIterations);
        }
        Pose sampledPose = poseSampler->samplePose();
        std::shared_ptr<TreeNode<Keyframe>> addedNodeStart = tryExtendTree(tree.get(), nnSearch.get(), sampledPose, true);
        std::shared_ptr<TreeNode<Keyframe>> addedNodeGoal = tryExtendTree(goalTree.get(), goalNNsearch.get(), sampledPose, false);
        if (addedNodeStart != nullptr && addedNodeGoal != nullptr &&
            distanceMetric->getDistance(addedNodeStart->pose, addedNodeGoal->pose) < config.connectionThreshold && canConnectTrees(addedNodeStart, addedNodeGoal))
        {
            spdlog::info("Solution found");
            return pathGenerator->generatePath(addedNodeStart, addedNodeGoal);
        }

    }
    spdlog::warn("TARRTconnectSolver: solution not found");
    throw std::runtime_error("TARRTconnectSolver: solution not found");
}



void TARRTconnectSolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    this->collisionHandler = std::dynamic_pointer_cast<IDynamicCollisionHandler>(manager->getComponent("CollisionHandler"));
    this->pathGenerator = std::dynamic_pointer_cast<ITreeConnectPathGenerator>(manager->getComponent("PathGenerator"));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch>(manager->getComponent("NearestNeighbourSearch"));
    std::unique_ptr<IComponent> uniqueNearestNeighbour = manager->getUniqueComponent("NearestNeighbourSearch");
    this->goalNNsearch = std::unique_ptr<AbstractNearestNeighbourSearch>(dynamic_cast<AbstractNearestNeighbourSearch*>(uniqueNearestNeighbour.get()));
    uniqueNearestNeighbour.release();
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler>(manager->getComponent("PoseSampler"));
    ATreeSolver::resolveDependencies(config, manager);
}

void TARRTconnectSolver::build()
{
    goalTree = std::make_unique<Tree<Keyframe>>(distanceMetric);
    ATreeSolver::build();
}

std::shared_ptr<TreeNode<Keyframe>> TARRTconnectSolver::tryExtendTree(Tree<Keyframe> *Tree,
                                                                      AbstractNearestNeighbourSearch *NNsearch,
                                                                      const Pose &sampledPose, bool isStartTree)
{
    int nearestNeighbourIndex = NNsearch->findNearestNeighbourIndex(sampledPose);

    std::shared_ptr<TreeNode<Keyframe>> nearestNeighbour = Tree->getNodes()[nearestNeighbourIndex];

    Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(nearestNeighbour->pose, sampledPose, config.maxStepSize, distanceMetric);
    double newTime;
    if (isStartTree)
        newTime = nearestNeighbour->pose.time + distanceMetric->getDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
    else
        newTime = nearestNeighbour->pose.time - distanceMetric->getDistance(nearestNeighbour->pose, poseWithinStepSize)/config.velocity;
    Keyframe keyframeWithinStepSize = PoseMath::poseToKeyframe(poseWithinStepSize, newTime);
    std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(nearestNeighbour->pose, keyframeWithinStepSize, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

    Keyframe* collidingKeyframe = nullptr;
    if (!collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe))
        return nullptr;

    std::shared_ptr<TreeNode<Keyframe>> newNode = Tree->addNode(keyframeWithinStepSize, nearestNeighbour);
    NNsearch->addPoint(keyframeWithinStepSize);
    return newNode;
}

bool TARRTconnectSolver::canConnectTrees(std::shared_ptr<TreeNode<Keyframe>> startTreeNode,
    std::shared_ptr<TreeNode<Keyframe>> goalTreeNode)
{
    std::vector<Keyframe> keyframesOnPath = KeyframeMath::interpolateKeyframes(startTreeNode->pose, goalTreeNode->pose, config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

    Keyframe* collidingKeyframe = nullptr;
    if (collisionHandler->areKeyframesCollisionFree(keyframesOnPath, collidingKeyframe) &&
        startTreeNode->pose.time + distanceMetric->getDistance(startTreeNode->pose, goalTreeNode->pose) < goalTreeNode->pose.time)
        return true;
    return false;
}
