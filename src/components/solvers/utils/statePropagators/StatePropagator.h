//
// Created by arseniy on 7.4.25.
//

#ifndef STATEPROPAGATOR_H
#define STATEPROPAGATOR_H
#include <memory>
#include <components/dynamicsSimulators/IDynamicsSimulator.h>
#include <components/sampling/controlInputSampling/IControlInputSampler.h>

#include "IStatePropagator.h"
#include "components/physics/physicsSimulator/PhysicsSimulator.h"
#include "components/propulsionSystem/IPropulsionSystem.h"

template <typename PositionType, typename ControlInputType>
class StatePropagator : public IStatePropagator<PositionType>
{
public:


    PositionType propagate(const PositionType &current) override;

    ComponentType getType() const override { return ComponentType::StatePropagator; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;;

protected:
    std::shared_ptr<IControlInputSampler<ControlInputType, PositionType>> controlInputSampler;
    std::shared_ptr<PhysicsSimulator<PositionType, ControlInputType>> physicsSimulator;
    std::shared_ptr<IPropulsionSystem<ControlInputType>> propulsionSystem;
};

template<typename PositionType, typename ControlInputType>
PositionType StatePropagator<PositionType, ControlInputType>::propagate(const PositionType &current)
{
    ControlInputType controlInput = controlInputSampler->sample(current);
    ControlInputPlan<ControlInputType> controlInputPlan = propulsionSystem->generateControlInputPlan(controlInput);
    PositionType nextState = physicsSimulator->computeNextState(current, controlInputPlan);
    return nextState;
}

template<typename PositionType, typename ControlInputType>
void StatePropagator<PositionType, ControlInputType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    IStatePropagator<PositionType>::resolveDependencies(config, manager);
    controlInputSampler = std::dynamic_pointer_cast<IControlInputSampler<ControlInputType, PositionType>>(
    manager->getComponent(ComponentType::ControlInputSampler));
    physicsSimulator = std::dynamic_pointer_cast<PhysicsSimulator<PositionType, ControlInputType>>(
        manager->getComponent(ComponentType::PhysicsSimulator));
    propulsionSystem = std::dynamic_pointer_cast<IPropulsionSystem<ControlInputType>>(
        manager->getComponent(ComponentType::PropulsionSystem));
}


#endif //STATEPROPAGATOR_H
