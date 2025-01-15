//
// Created by arseniy on 12.10.24.
//

#include "RrtStarSolver.h"

std::vector<Pose> RrtStarSolver::solve(const Pose& startPosition, const Pose& goalPosition)
{
    tree->initializeTree(startPosition);
    nnSearch->addPoint(startPosition);
    std::vector<int> nearestNeighboursIndexes;
    std::vector<int> collisionFreeNeighboursIndexes;
    int minCostParentIndex = -1;
    for (int i=0; i<config.maxIterations; i++)
    {
        collisionFreeNeighboursIndexes.clear();
        Pose sampledPose = poseSampler->samplePose();
        minCostParentIndex = findMinCostParent(sampledPose, collisionFreeNeighboursIndexes);

        if (minCostParentIndex == -1)
            continue;

        const std::shared_ptr<TreeNode<Pose>>& parent = tree->getNodes()[minCostParentIndex];
        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(parent->pose, sampledPose, config.maxStepSize, distanceMetric);


        auto newNode = tree->addNode(poseWithinStepSize, parent);
        nnSearch->addPoint(poseWithinStepSize);
        tree->rewireTree(newNode, collisionFreeNeighboursIndexes, collisionHandler);
    }
    minCostParentIndex = findMinCostParent(goalPosition, collisionFreeNeighboursIndexes);
    if (minCostParentIndex == -1)
        throw std::runtime_error("RrtStarSolver::solve(): No solution found");
    const std::shared_ptr<TreeNode<Pose>>& goalParent = tree->getNodes()[minCostParentIndex];
    return pathGenerator->generatePath(goalParent);
}

void RrtStarSolver::resolveDependencies(ComponentConfig &config, ComponentManager *manager)
{
    AbstractTreeSolver<RrtStarSolverConfig>::resolveDependencies(config, manager);
    this->collisionHandler = std::dynamic_pointer_cast<ICollisionHandler>(manager->getComponent("CollisionHandler"));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch>(manager->getComponent("NearestNeighbourSearch"));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler>(manager->getComponent("PoseSampler"));
}

int RrtStarSolver::findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes)
{
    std::vector<int> nearestNeighboursIndexes = nnSearch->findKnearestNeighboursIndexes(pose);
    double minCost = std::numeric_limits<double>::max();
    int chosenIndex = -1;
    for (auto idx : nearestNeighboursIndexes)
    {
        auto neighbour = tree->getNodes()[idx];
        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(neighbour->pose, pose, config.maxStepSize, distanceMetric);
        std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(neighbour->pose, poseWithinStepSize,
                                                                    config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        if (!collisionHandler->arePosesCollisionFree(posesOnPath))
            continue;

        collisionFreeNeighboursIndexes.push_back(idx);

        double cost = neighbour->getCost() + distanceMetric->getDistance(neighbour->pose, poseWithinStepSize);
        if (cost < minCost)
        {
            minCost = cost;
            chosenIndex = idx;
        }
    }
    return chosenIndex;
}
