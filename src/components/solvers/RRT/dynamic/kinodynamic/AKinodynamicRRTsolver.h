//
// Created by arseniy on 20.3.25.
//

#ifndef AKINODYNAMICRRTSOLVER_H
#define AKINODYNAMICRRTSOLVER_H
#include "components/constraintsEnforcer/IConstraintsEnforcer.h"
#include "components/dynamicsSimulators/IDynamicsSimulator.h"
#include "components/propulsionSystem/IPropulsionSystem.h"
#include "components/sampling/controlInputSampling/IControlInputSampler.h"
#include "components/solvers/RRT/AGeometricRRTsolver.h"
#include "components/solvers/utils/statePropagators/IStatePropagator.h"

template <typename PositionType, typename TargetType, typename SampleType>
class AKinodynamicRRTsolver : public ARRTsolver<PositionType, TargetType, SampleType>
{
public:
    AKinodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
        : ARRTsolver<PositionType, TargetType, SampleType>(maxIterations, outputPeriod), controlInputSamples(controlInputSamples)
    {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    int controlInputSamples;
    std::shared_ptr<IConstraintsEnforcer<PositionType>> constraintsEnforcer;
    std::shared_ptr<IStatePropagator<PositionType>> statePropagator;

    std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour,
        const SampleType &sample, const TargetType &target) override;

    PositionType propagate(const PositionType& current);

    virtual bool isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType& nextState);
    virtual std::shared_ptr<TreeNode<PositionType>> extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);

};

template<typename PositionType, typename TargetType, typename SampleType>
void AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(
    const ComponentConfig &config, ComponentManager *manager)
{
    ARRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(config, manager);
    constraintsEnforcer = std::dynamic_pointer_cast<IConstraintsEnforcer<PositionType>>(
        manager->getComponent(ComponentType::ConstraintsEnforcer));
    statePropagator = std::dynamic_pointer_cast<IStatePropagator<PositionType>>(
        manager->getComponent(ComponentType::StatePropagator));
}



template<typename PositionType, typename TargetType, typename SampleType>
std::optional<std::shared_ptr<TreeNode<PositionType>>> AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::
growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType &sample, const TargetType &target)
{
    const PositionType& currentState = neighbour->pose;
    for (int j=0; j<this->controlInputSamples; j++)
    {
        PositionType nextState = propagate(currentState);
        if (!this->isTransitionValid(neighbour, nextState))
            continue;
        nextState.validate("mainLoop");
        std::shared_ptr<TreeNode<PositionType>> newNode = this->extendTree(neighbour, nextState);
        if (this->isTargetReached(newNode, target))
            return newNode;
    }
    return std::nullopt;
}

template<typename PositionType, typename TargetType, typename SampleType>
PositionType AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::propagate(
    const PositionType &current)
{
    return this->statePropagator->propagate(current);
}

template<typename PositionType, typename TargetType, typename SampleType>
bool AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::isTransitionValid(
    std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType &nextState)
{
    return this->constraintsEnforcer->satisfiesConstraints(nextState) &&
        this->collisionHandler->isTransitionValid(neighbor->pose, nextState);
}

template<typename PositionType, typename TargetType, typename SampleType>
std::shared_ptr<TreeNode<PositionType>> AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::
extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType &extendedPosition)
{
    std::shared_ptr<TreeNode<PositionType>> newNode = std::make_shared<TreeNode<PositionType>>(extendedPosition, neighbor, 0.0);
    this->nnSearch->add(newNode);
    ++this->totalNodes;
    neighbor->children.push_back(newNode);
    return newNode;
}

#endif //AKINODYNAMICRRTSOLVER_H
