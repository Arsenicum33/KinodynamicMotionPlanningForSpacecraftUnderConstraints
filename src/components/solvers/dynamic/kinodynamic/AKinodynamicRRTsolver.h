//
// Created by arseniy on 20.3.25.
//

#ifndef AKINODYNAMICRRTSOLVER_H
#define AKINODYNAMICRRTSOLVER_H
#include "components/sampling/controlInputSampling/IControlInputSampler.h"
#include "components/solvers/AGeometricRRTsolver.h"
#include "dto/poses/dynamic/kinodynamic/controlInput/ControlInput.h"

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
    std::shared_ptr<IControlInputSampler<ControlInput>> controlInputSampler;
    ControlInput sampleControlInput() const;
    PositionType computeNextState(const PositionType& currentState, const ControlInput& input);

    std::optional<std::shared_ptr<TreeNode<PositionType>>> growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour,
        const SampleType &sample, const TargetType &target) override;

};

template<typename PositionType, typename TargetType, typename SampleType>
void AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(
    const ComponentConfig &config, ComponentManager *manager)
{
    ARRTsolver<PositionType, TargetType, SampleType>::resolveDependencies(config, manager);
    controlInputSampler = std::dynamic_pointer_cast<IControlInputSampler<ControlInput>>(
        manager->getComponent(ComponentType::ControlInputSampler));

}

template<typename PositionType, typename TargetType, typename SampleType>
ControlInput AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::sampleControlInput() const
{
    return controlInputSampler->sample();
}

template<typename PositionType, typename TargetType, typename SampleType>
PositionType AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::computeNextState(
    const PositionType &currentState, const ControlInput &input)
{
}

template<typename PositionType, typename TargetType, typename SampleType>
std::optional<std::shared_ptr<TreeNode<PositionType>>> AKinodynamicRRTsolver<PositionType, TargetType, SampleType>::
growTowardTarget(std::shared_ptr<TreeNode<PositionType>> neighbour, const SampleType &sample, const TargetType &target)
{
    const PositionType& currentState = neighbour->pose;
    for (int j=0; j<this->controlInputSamples; j++)
    {
        ControlInput controlInput = sampleControlInput();
        PositionType nextState = computeNextState(currentState, controlInput);
        if (!isTransitionValid(neighbour, nextState))
            continue;
        std::shared_ptr<TreeNode<PositionType>> newNode = extendTree(neighbour, nextState);
        if (isTargetReached(newNode, target))
            return newNode;
    }
    return std::nullopt;
}

#endif //AKINODYNAMICRRTSOLVER_H
