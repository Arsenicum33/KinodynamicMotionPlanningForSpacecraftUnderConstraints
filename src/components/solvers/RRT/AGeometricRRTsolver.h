// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef AGEOMETRICRRTSOLVER_H
#define AGEOMETRICRRTSOLVER_H
#include <components/collisionHandlers/ICollisionHandler.h>
#include <components/solvers/RRT/treeUtils/Tree.h>

#include "ARRTsolver.h"
#include "../ISolver.h"
#include "components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h"
#include "components/interpolators/IInterpolator.h"
#include "components/pathGenerator/tree/ITreePathGenerator.h"
#include "../../sampling/positionSampling/IPositionSampler.h"
#include "components/terminationConditions/ITerminationCondition.h"

template <typename PositionType, typename TargetType, typename SampleType>
class AGeometricRRTsolver : public ARRTsolver<PositionType, TargetType, SampleType>
{
public:
    AGeometricRRTsolver(int maxIterations,  double maxStepSize, int outputPeriod)
        : ARRTsolver<PositionType, TargetType, SampleType>(maxIterations, outputPeriod), maxStepSize(maxStepSize) {}

protected:
    double maxStepSize;

    virtual PositionType getExtendedPosition(std::shared_ptr<const TreeNode<PositionType>> neighbor, const SampleType& sample);
    virtual bool isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);
    virtual std::shared_ptr<TreeNode<PositionType>> extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);

    std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour,
        const SampleType &sample, const TargetType &target) override;
};

template<typename PositionType, typename TargetType, typename SampleType>
PositionType AGeometricRRTsolver<PositionType, TargetType, SampleType>::getExtendedPosition(
    std::shared_ptr<const TreeNode<PositionType>> neighbor, const SampleType &sample)
{
    return this->interpolator->getIntermediatePosition(neighbor->pose, sample, this->maxStepSize);
}

template<typename PositionType, typename TargetType, typename SampleType>
bool AGeometricRRTsolver<PositionType, TargetType, SampleType>::isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor,
    const PositionType &extendedPosition)
{
    std::vector<PositionType> interpolatedPositions = this->interpolator->interpolate(neighbor->pose, extendedPosition);
    return this->collisionHandler->areCollisionFree(interpolatedPositions);
}

template<typename PositionType, typename TargetType, typename SampleType>
std::shared_ptr<TreeNode<PositionType>> AGeometricRRTsolver<PositionType, TargetType, SampleType>::extendTree(
    std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType &extendedPosition)
{
    std::shared_ptr<TreeNode<PositionType>> newNode = std::make_shared<TreeNode<PositionType>>(extendedPosition, neighbor, 0.0);
    this->nnSearch->add(newNode);
    ++this->totalNodes;
    return newNode;
}

template<typename PositionType, typename TargetType, typename SampleType>
std::optional<std::shared_ptr<TreeNode<PositionType>>> AGeometricRRTsolver<PositionType, TargetType, SampleType>::growTowardTarget(
    std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType &sample, const TargetType &target)
{
    PositionType extendedPosition = getExtendedPosition(neighbour, sample);
    if (!this->isTransitionValid(neighbour, extendedPosition))
        return std::nullopt;
    std::shared_ptr<TreeNode<PositionType>> newNode = extendTree(neighbour, extendedPosition);
    if (this->isTargetReached(newNode, target))
        return newNode;
    return std::nullopt;
}


#endif //AGEOMETRICRRTSOLVER_H
