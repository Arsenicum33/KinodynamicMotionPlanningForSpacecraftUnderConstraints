//
// Created by arseniy on 16.3.25.
//

#ifndef ARRTSOLVER_H
#define ARRTSOLVER_H
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/nearestNeighbour/AbstractNearestNeighbourSearch.h>
#include <components/solvers/treeUtils/Tree.h>

#include "ISolver.h"
#include "components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h"
#include "components/interpolators/IInterpolator.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "components/sampling/ISampler.h"
#include "components/terminationConditions/ITerminationCondition.h"

template <typename PositionType, typename TargetType>
class ARRTsolver : public ISolver
{
public:
    ARRTsolver(int maxIterations, double maxStepSize, int outputPeriod) :
        maxIterations(maxIterations), maxStepSize(maxStepSize), outputPeriod(outputPeriod) {}
    std::vector<std::any> solve(const std::any &start, const std::any &target) final;
    void build() override;
    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;
protected:
    virtual std::vector<PositionType> solveTyped(const PositionType& start, const TargetType& target);
    virtual void initialize(const PositionType& start);
    virtual void outputIteration(int currentIteration);
    virtual PositionType sample(const TargetType& target);
    virtual std::shared_ptr<TreeNode<PositionType>> findNearestNeighbour(const PositionType& sample);
    virtual PositionType getExtendedPosition(std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType& sample);
    virtual bool isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);
    virtual std::shared_ptr<TreeNode<PositionType>> extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);
    virtual bool isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode, const TargetType& target);
    virtual std::vector<PositionType> extractPath(std::shared_ptr<const TreeNode<PositionType>> finalNode);
    virtual std::vector<PositionType> handleSolutionNotFound();

    int maxIterations;
    int outputPeriod;
    double maxStepSize;
    std::shared_ptr<AbstractNearestNeighbourSearch<PositionType>> nnSearch;
    std::shared_ptr<ISampler<PositionType, TargetType>> sampler;
    std::shared_ptr<ICollisionHandler<PositionType>> collisionHandler;
    std::shared_ptr<ITreePathGenerator<PositionType>> pathGenerator;
    std::shared_ptr<ITerminationCondition<PositionType, TargetType>> terminationCondition;
    std::shared_ptr<IInterpolator<PositionType>> interpolator;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::unique_ptr<Tree<PositionType>> tree;
private:
    std::vector<std::any> toAnyVector(std::vector<PositionType> result);
};

template<typename PositionType, typename TargetType>
std::vector<std::any> ARRTsolver<PositionType, TargetType>::solve(const std::any &start, const std::any &target)
{
    try
    {
        std::vector<PositionType> result = solveTyped(std::any_cast<const PositionType>(start), std::any_cast<const TargetType>(target));
        return toAnyVector(result);
    }
    catch (std::bad_any_cast e)
    {
        spdlog::error("ARRTsolver::solve(): bad any cast.");
        throw e;
    }
}


template<typename PositionType, typename TargetType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType>::solveTyped(const PositionType &start,
    const TargetType &target)
{
    initialize(start);
    for (int i=0; i<maxIterations; i++)
    {
        outputIteration(i);
        PositionType sample = sampler->sample(target);
        std::shared_ptr<TreeNode<PositionType>> nearestNeighbour = findNearestNeighbour(sample);
        PositionType extendedPosition = getExtendedPosition(nearestNeighbour, sample);
        if (!isTransitionValid(nearestNeighbour, extendedPosition))
            continue;
        std::shared_ptr<TreeNode<PositionType>> newNode = extendTree(nearestNeighbour, extendedPosition);
        if (isTargetReached(newNode, target))
        {
            return extractPath(newNode);
        }
    }
    return handleSolutionNotFound();
}

template<typename PositionType, typename TargetType>
void ARRTsolver<PositionType, TargetType>::initialize(const PositionType &start)
{
    spdlog::info("Solver {} started!");
    tree->initializeTree(start);
    nnSearch->addPoint(start);
}

template<typename PositionType, typename TargetType>
void ARRTsolver<PositionType, TargetType>::outputIteration(int currentIteration)
{
    if ((currentIteration+1) % outputPeriod == 0)
    {
        spdlog::info("Iteration {}/{}", currentIteration+1, maxIterations);
    }
}

template<typename PositionType, typename TargetType>
PositionType ARRTsolver<PositionType, TargetType>::sample(const TargetType &target)
{
    return sampler->sample(target);
}

template<typename PositionType, typename TargetType>
std::shared_ptr<TreeNode<PositionType>> ARRTsolver<PositionType, TargetType>::findNearestNeighbour(
    const PositionType &sample)
{
    int index = nnSearch->findNearestNeighbourIndex(sample);
    return tree->getNodes()[index];
}

template<typename PositionType, typename TargetType>
PositionType ARRTsolver<PositionType, TargetType>::getExtendedPosition(
    std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType &sample)
{
    return interpolator->getIntermediatePosition(neighbor->pose, sample, maxStepSize);
}

template<typename PositionType, typename TargetType>
bool ARRTsolver<PositionType, TargetType>::isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor,
    const PositionType &extendedPosition)
{
    std::vector<PositionType> interpolatedPositions = interpolator->interpolate(neighbor->pose, extendedPosition);
    return collisionHandler->areCollisionFree(interpolatedPositions);
}

template<typename PositionType, typename TargetType>
std::shared_ptr<TreeNode<PositionType>> ARRTsolver<PositionType, TargetType>::extendTree(
    std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType &extendedPosition)
{
    std::shared_ptr<TreeNode<PositionType>> newNode = tree->addNode(extendedPosition, neighbor);
    nnSearch->addPoint(extendedPosition);
    return newNode;
}

template<typename PositionType, typename TargetType>
bool ARRTsolver<PositionType, TargetType>::isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode,
    const TargetType &target)
{
    return terminationCondition->isTargetReached(newNode->pose, target);
}

template<typename PositionType, typename TargetType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType>::extractPath(
    std::shared_ptr<const TreeNode<PositionType>> finalNode)
{
    spdlog::info("Solution found!");
    return pathGenerator->generatePath(finalNode);
}

template<typename PositionType, typename TargetType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType>::handleSolutionNotFound()
{
    spdlog::error("Solution NOT found!");
    throw std::runtime_error("Solution NOT found!");
}

template<typename PositionType, typename TargetType>
std::vector<std::any> ARRTsolver<PositionType, TargetType>::toAnyVector(std::vector<PositionType> result)
{
    std::vector<std::any> resultAsAny;
    resultAsAny.reserve(result.size());
    for (const auto& item : result)
    {
        resultAsAny.push_back(item);
    }
    return resultAsAny;
}


template<typename PositionType, typename TargetType>
void ARRTsolver<PositionType, TargetType>::build()
{
    ISolver::build();
}

template<typename PositionType, typename TargetType>
void ARRTsolver<PositionType, TargetType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ISolver::resolveDependencies(config, manager);
    nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<PositionType>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    sampler = std::dynamic_pointer_cast<ISampler<PositionType, TargetType>>(manager->getComponent(ComponentType::Sampler));
    collisionHandler = std::dynamic_pointer_cast<ICollisionHandler<PositionType>>(manager->getComponent(ComponentType::CollisionHandler));
    pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<PositionType>>(manager->getComponent(ComponentType::PathGenerator));
    terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<PositionType, TargetType>>(manager->getComponent(ComponentType::TerminationCondition));
    interpolator = std::dynamic_pointer_cast<IInterpolator<PositionType>>(manager->getComponent(ComponentType::Interpolator));
    distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    tree = std::make_unique<Tree<PositionType>>(distanceMetric, interpolator, collisionHandler);
}


#endif //ARRTSOLVER_H
