//
// Created by arseniy on 12.10.24.
//

#include "RrtStarSolver.h"

#include <spdlog/spdlog.h>

std::unique_ptr<IComponent> RrtStarSolver::createComponent(const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    int maxIterations = std::any_cast<double>(configMap.at("maxIterations"));
    double maxStepSize = std::any_cast<double>(configMap.at("maxStepSize"));

    return std::make_unique<RrtStarSolver>(maxIterations, maxStepSize);
}

std::vector<Pose> RrtStarSolver::solve(const Pose& startPosition, const Pose& goalPosition)
{
    tree->initializeTree(startPosition);
    nnSearch->addPoint(startPosition);
    std::vector<int> nearestNeighboursIndexes;
    std::vector<int> collisionFreeNeighboursIndexes;
    int minCostParentIndex = -1;
    int outputIterationsPeriod = 10000;
    for (int i=0; i<config.maxIterations; i++)
    {
        if ((i+1) % outputIterationsPeriod == 0)
        {
            spdlog::info("Iteration {}/{}", i+1, config.maxIterations);
        }

        collisionFreeNeighboursIndexes.clear();
        Pose sampledPose = poseSampler->samplePose(goalPosition);
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
    {
        spdlog::warn("RrtStarSolver: solution not found");
        throw std::runtime_error("RrtStarSolver: solution not found");
    }
    const std::shared_ptr<TreeNode<Pose>>& goalParent = tree->getNodes()[minCostParentIndex];
    spdlog::info("Solution found");
    return pathGenerator->generatePath(goalParent);
}

void RrtStarSolver::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ATreeSolver::resolveDependencies(config, manager);
    this->collisionHandler = std::dynamic_pointer_cast<ICollisionHandler>(manager->getComponent(ComponentType::CollisionHandler));
    this->nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<Pose>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    this->poseSampler = std::dynamic_pointer_cast<IPoseSampler<Pose>>(manager->getComponent(ComponentType::Sampler));
    this->pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<Pose>>(manager->getComponent(ComponentType::PathGenerator));
}

int RrtStarSolver::findMinCostParent(const Pose& pose, std::vector<int>& collisionFreeNeighboursIndexes)
{
    std::vector<int> nearestNeighboursIndexes = nnSearch->findKnearestNeighboursIndexes(pose);
    double minCost = std::numeric_limits<double>::max();
    int chosenIndex = -1;
    for (auto idx : nearestNeighboursIndexes)
    {
        auto neighbour = tree->getNodes()[idx];
        Pose poseWithinStepSize = PoseMath::getPoseWithinStepSize(neighbour->pose, pose, config.maxStepSize, std::static_pointer_cast<IDistanceMetric>(distanceMetric));
        std::vector<Pose> posesOnPath = PoseMath::interpolatePoses(neighbour->pose, poseWithinStepSize,
                                                                    config.interpolationDistanceThreshold, config.interpolationRotationDistanceThreshold);

        Pose* collisionResult = nullptr;
        if (!collisionHandler->arePosesCollisionFree(posesOnPath, collisionResult))
            continue;

        collisionFreeNeighboursIndexes.push_back(idx);

        double cost = neighbour->getCost() + distanceMetric->getSpatialDistance(neighbour->pose, poseWithinStepSize);
        if (cost < minCost)
        {
            minCost = cost;
            chosenIndex = idx;
        }
    }
    return chosenIndex;
}
