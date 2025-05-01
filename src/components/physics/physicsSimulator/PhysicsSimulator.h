//
// Created by arseniy on 10.4.25.
//

#ifndef PHYSICSSIMULATOR_H
#define PHYSICSSIMULATOR_H
#include <components/dynamicsSimulators/IDynamicsSimulator.h>

#include "IPhysicsSimulator.h"
#include "components/physics/externalForceComputer/ExternalForcesComputer.h"
#include "components/physics/forceToAccelerationConverter/IForceToAccelerationConverter.h"
#include "components/physics/internalForcesComputer/InternalForcesComputer.h"
#include "components/fuelSystem/IFuelSystem.h"
template <typename StateType>
class PhysicsSimulator : public IPhysicsSimulator<StateType>
{
public:
    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }


    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

    TotalAcceleration computeAcceleration(
        const StateType &currentState, const BurstControlInput &controlInput) override;

protected:
    std::shared_ptr<InternalForcesComputer<StateType>> internalForcesComputer;
    std::shared_ptr<ExternalForcesComputer<StateType>> externalForcesComputer;
    std::shared_ptr<IForceToAccelerationConverter<StateType>> forceToAccelerationConverter;
    std::shared_ptr<IFuelSystem> fuelSystem;
};

template<typename StateType>
TotalAcceleration PhysicsSimulator<StateType>::computeAcceleration(const StateType &currentState,
    const BurstControlInput &controlInput)
{
    TotalForce internalForce = internalForcesComputer->computeTotalForce(currentState, controlInput);
    TotalForce externalForce = externalForcesComputer->computeTotalForce(currentState);
    TotalForce total = internalForce + externalForce;
    TotalAcceleration acceleration = forceToAccelerationConverter->convert(total, currentState);
    return acceleration;
}


template<typename StateType>
void PhysicsSimulator<StateType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    IPhysicsSimulator<StateType>::resolveDependencies(config, manager);
    internalForcesComputer = std::dynamic_pointer_cast<InternalForcesComputer<StateType>>(
        manager->getComponent(ComponentType::InternalForcesComputer));
    externalForcesComputer = std::dynamic_pointer_cast<ExternalForcesComputer<StateType>>(
        manager->getComponent(ComponentType::ExternalForcesComputer));
    forceToAccelerationConverter = std::dynamic_pointer_cast<IForceToAccelerationConverter<StateType>>(
        manager->getComponent(ComponentType::ForceToAccelerationConverter));
    fuelSystem = std::dynamic_pointer_cast<IFuelSystem>(
        manager->getComponent(ComponentType::FuelSystem));
}



#endif //PHYSICSSIMULATOR_H
