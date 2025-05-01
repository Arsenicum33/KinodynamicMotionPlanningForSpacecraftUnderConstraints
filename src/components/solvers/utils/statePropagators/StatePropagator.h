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
#include "components/planner/IPlanner.h"
#include "components/propulsionSystem/IPropulsionSystem.h"

template <typename PositionType>
class StatePropagator : public IStatePropagator<PositionType>
{
public:


    PositionType propagate(const PositionType &current) override;

    ComponentType getType() const override { return ComponentType::StatePropagator; }

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;;

protected:
    std::shared_ptr<IControlInputSampler<BurstControlInput, PositionType>> controlInputSampler;
    std::shared_ptr<IPlanner<PositionType>> planner;
    std::shared_ptr<IPropulsionSystem<BurstControlInput>> propulsionSystem;
};

template<typename PositionType>
PositionType StatePropagator<PositionType>::propagate(const PositionType &current)
{
    BurstControlInput controlInput = controlInputSampler->sample(current);
    ControlInputPlan controlInputPlan = propulsionSystem->generateControlInputPlan(controlInput);
    PositionType nextState = planner->executeControlInputPlan(current, controlInputPlan);
    return nextState;
}

template<typename PositionType>
void StatePropagator<PositionType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    IStatePropagator<PositionType>::resolveDependencies(config, manager);
    controlInputSampler = std::dynamic_pointer_cast<IControlInputSampler<BurstControlInput, PositionType>>(
    manager->getComponent(ComponentType::ControlInputSampler));
    planner = std::dynamic_pointer_cast<IPlanner<PositionType>>(
        manager->getComponent(ComponentType::Planner));
    propulsionSystem = std::dynamic_pointer_cast<IPropulsionSystem<BurstControlInput>>(
        manager->getComponent(ComponentType::PropulsionSystem));
}


#endif //STATEPROPAGATOR_H
