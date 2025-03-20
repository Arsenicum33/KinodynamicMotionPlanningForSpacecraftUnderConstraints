//
// Created by arseniy on 20.3.25.
//

#ifndef ARRTSOLVER_H
#define ARRTSOLVER_H
#include "ISolver.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "../sampling/positionSampling/IPositionSampler.h"
#include "components/terminationConditions/ITerminationCondition.h"
#include <optional>

template <typename PositionType, typename TargetType, typename SampleType>
class ARRTsolver : public ISolver
{
public:
    ARRTsolver(int maxIterations, double maxStepSize, int outputPeriod)
        : maxIterations(maxIterations),
          outputPeriod(outputPeriod) {}

    std::vector<std::any> solve(const std::any &start, const std::any &target) final;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::vector<PositionType> solveTyped(const PositionType& start, const TargetType& target);

    virtual void initialize(const PositionType& start);
    virtual void outputIteration(int currentIteration);
    virtual SampleType samplePosition(const TargetType& target);
    virtual std::shared_ptr<TreeNode<PositionType>> findNearestNeighbour(const SampleType& sample);
    virtual std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(
        std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType& sample, const TargetType& target) = 0;
    virtual bool isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode, const TargetType& target);
    virtual std::vector<PositionType> extractPath(std::shared_ptr<const TreeNode<PositionType>> finalNode);
    virtual std::vector<PositionType> handleSolutionNotFound();

    int maxIterations;
    int outputPeriod;

    std::shared_ptr<AbstractNearestNeighbourSearch<SampleType>> nnSearch;
    std::unique_ptr<Tree<PositionType>> tree;
    std::shared_ptr<IPositionSampler<SampleType, TargetType>> positionSampler;
    std::shared_ptr<ICollisionHandler<PositionType>> collisionHandler;
    std::shared_ptr<IInterpolator<PositionType>> interpolator;
    std::shared_ptr<IDistanceMetric> distanceMetric;
    std::shared_ptr<ITreePathGenerator<PositionType>> pathGenerator;
    std::shared_ptr<ITerminationCondition<PositionType, TargetType>> terminationCondition;
private:
    std::vector<std::any> toAnyVector(std::vector<PositionType> result);
};


template<typename PositionType, typename TargetType, typename SampleType>
std::vector<std::any> ARRTsolver<PositionType, TargetType, SampleType>::solve(const std::any &start, const std::any &target)
{
    try
    {
        std::vector<PositionType> result = solveTyped(std::any_cast<const PositionType>(start), std::any_cast<const TargetType>(target));
        return toAnyVector(result);
    }
    catch (std::bad_any_cast e)
    {
        spdlog::error("ARRTsolver::solve(): bad any cast.");
        throw;
    }
}

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::solveTyped(const PositionType &start,
    const TargetType &target)
{
    initialize(start);
    for (int i=0; i<maxIterations; i++)
    {
        outputIteration(i);
        SampleType sample = samplePosition(target);
        std::shared_ptr<TreeNode<PositionType>> neighbour = findNearestNeighbour(sample);
        std::optional<std::shared_ptr<TreeNode<PositionType>>> resultNode = growTowardTarget(neighbour, sample, target);
        if (resultNode.has_value() && isTargetReached(*resultNode, target))
        {
            return extractPath(*resultNode);
        }
    }
    return handleSolutionNotFound();
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::initialize(const PositionType &start)
{
    spdlog::info("Solver started!");
    tree->initializeTree(start);
    nnSearch->addPoint(start);
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::outputIteration(int currentIteration)
{
    if ((currentIteration+1) % outputPeriod == 0)
    {
        spdlog::info("Iteration {}/{}", currentIteration+1, maxIterations);
    }
}

template<typename PositionType, typename TargetType, typename SampleType>
SampleType ARRTsolver<PositionType, TargetType, SampleType>::samplePosition(const TargetType &target)
{
    return positionSampler->sample(target);
}


template<typename PositionType, typename TargetType, typename SampleType>
std::shared_ptr<TreeNode<PositionType>> ARRTsolver<PositionType, TargetType, SampleType>::findNearestNeighbour(
    const SampleType &sample)
{
    int index = nnSearch->findNearestNeighbourIndex(sample);
    return tree->getNodes()[index];
}


template<typename PositionType, typename TargetType, typename SampleType>
bool ARRTsolver<PositionType, TargetType, SampleType>::isTargetReached(std::shared_ptr<const TreeNode<PositionType>> newNode,
    const TargetType &target)
{
    return terminationCondition->isTargetReached(newNode->pose, target);
}


template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::extractPath(
    std::shared_ptr<const TreeNode<PositionType>> finalNode)
{
    spdlog::info("Solution found!");
    return pathGenerator->generatePath(finalNode);
}

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<PositionType> ARRTsolver<PositionType, TargetType, SampleType>::handleSolutionNotFound()
{
    spdlog::error("Solution NOT found!");
    throw std::runtime_error("Solution NOT found!");
}

template<typename PositionType, typename TargetType, typename SampleType>
std::vector<std::any> ARRTsolver<PositionType, TargetType, SampleType>::toAnyVector(std::vector<PositionType> result)
{
    std::vector<std::any> resultAsAny;
    resultAsAny.reserve(result.size());
    for (const auto& item : result)
    {
        resultAsAny.push_back(item);
    }
    return resultAsAny;
}

template<typename PositionType, typename TargetType, typename SampleType>
void ARRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(const ComponentConfig &config, ComponentManager *manager)
{
    ISolver::resolveDependencies(config, manager);
    nnSearch = std::dynamic_pointer_cast<AbstractNearestNeighbourSearch<PositionType>>(manager->getComponent(ComponentType::NearestNeighbourSearch));
    collisionHandler = std::dynamic_pointer_cast<ICollisionHandler<PositionType>>(manager->getComponent(ComponentType::CollisionHandler));
    interpolator = std::dynamic_pointer_cast<IInterpolator<PositionType>>(manager->getComponent(ComponentType::Interpolator));
    distanceMetric = std::dynamic_pointer_cast<IDistanceMetric>(manager->getComponent(ComponentType::DistanceMetric));
    positionSampler = std::dynamic_pointer_cast<IPositionSampler<SampleType, TargetType>>(manager->getComponent(ComponentType::PositionSampler));
    pathGenerator = std::dynamic_pointer_cast<ITreePathGenerator<PositionType>>(manager->getComponent(ComponentType::PathGenerator));
    terminationCondition = std::dynamic_pointer_cast<ITerminationCondition<PositionType, TargetType>>(manager->getComponent(ComponentType::TerminationCondition));
    tree = std::make_unique<Tree<PositionType>>(distanceMetric, interpolator, collisionHandler);
}

#endif //ARRTSOLVER_H
