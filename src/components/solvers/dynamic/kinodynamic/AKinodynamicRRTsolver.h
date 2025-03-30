//
// Created by arseniy on 20.3.25.
//

#ifndef AKINODYNAMICRRTSOLVER_H
#define AKINODYNAMICRRTSOLVER_H
#include "components/constraintsEnforcer/IConstraintsEnforcer.h"
#include "components/dynamicsSimulators/IDynamicsSimulator.h"
#include "components/sampling/controlInputSampling/IControlInputSampler.h"
#include "components/solvers/AGeometricRRTsolver.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"

template <typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
class AKinodynamicRRTsolver : public ARRTsolver<PositionType, TargetType, SampleType>
{
public:
    AKinodynamicRRTsolver(int maxIterations, int outputPeriod, int controlInputSamples)
        : ARRTsolver<PositionType, TargetType, SampleType>(maxIterations, outputPeriod), controlInputSamples(controlInputSamples)
    {}

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    int controlInputSamples;
    std::shared_ptr<IControlInputSampler<ControlInputType, PositionType>> controlInputSampler;
    std::shared_ptr<IDynamicsSimulator<PositionType, ControlInput>> dynamicsSimulator;
    std::shared_ptr<IConstraintsEnforcer<PositionType>> constraintsEnforcer;
    ControlInput sampleControlInput(const PositionType& current) const;
    PositionType computeNextState(const PositionType& currentState, const ControlInput& input);

    std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour,
        const SampleType &sample, const TargetType &target) override;

    virtual bool isTransitionValid(std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType& nextState);
    virtual std::shared_ptr<TreeNode<PositionType>> extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType& extendedPosition);

};

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
void AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::resolveDependencies(
    const ComponentConfig &config, ComponentManager *manager)
{
    ARRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(config, manager);
    controlInputSampler = std::dynamic_pointer_cast<IControlInputSampler<ControlInput, PositionType>>(
        manager->getComponent(ComponentType::ControlInputSampler));
    dynamicsSimulator = std::dynamic_pointer_cast<IDynamicsSimulator<PositionType, ControlInputType>>(
        manager->getComponent(ComponentType::DynamicsSimulator));
    constraintsEnforcer = std::dynamic_pointer_cast<IConstraintsEnforcer<PositionType>>(
        manager->getComponent(ComponentType::ConstraintsEnforcer));
}

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
ControlInput AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::sampleControlInput(const PositionType& current) const
{
    return controlInputSampler->sample(current);
}

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
PositionType AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::computeNextState(
    const PositionType &currentState, const ControlInput &input)
{
    return dynamicsSimulator->computeNextState(currentState, input);
}

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
std::optional<std::shared_ptr<TreeNode<PositionType>>> AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::
growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType &sample, const TargetType &target)
{
    const PositionType& currentState = neighbour->pose;
    for (int j=0; j<this->controlInputSamples; j++)
    {
        ControlInput controlInput = sampleControlInput(currentState);
        PositionType nextState = computeNextState(currentState, controlInput);
        if (!this->isTransitionValid(neighbour, nextState))
            continue;
        std::shared_ptr<TreeNode<PositionType>> newNode = this->extendTree(neighbour, nextState);
        if (this->isTargetReached(newNode, target))
            return newNode;
    }
    return std::nullopt;
}

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
bool AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::isTransitionValid(
    std::shared_ptr<const TreeNode<PositionType>> neighbor, const PositionType &nextState)
{
    return this->constraintsEnforcer->satisfiesConstraints(nextState) &&
        this->collisionHandler->isTransitionValid(neighbor->pose, nextState);
}

template<typename PositionType, typename TargetType, typename SampleType, typename ControlInputType>
std::shared_ptr<TreeNode<PositionType>> AKinodynamicRRTsolver<PositionType, TargetType, SampleType, ControlInputType>::
extendTree(std::shared_ptr<TreeNode<PositionType>> neighbor, const PositionType &extendedPosition)
{
    std::shared_ptr<TreeNode<PositionType>> newNode = this->tree->addNode(extendedPosition, neighbor);
    this->nnSearch->addPoint(extendedPosition);
    return newNode;
}

#endif //AKINODYNAMICRRTSOLVER_H
