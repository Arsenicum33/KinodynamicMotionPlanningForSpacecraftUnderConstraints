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

template <typename StateType, typename ControlInputType>
class PhysicsSimulator : public IPhysicsSimulator<StateType, ControlInputType>
{
public:
    explicit PhysicsSimulator(double timeResolution)
        : timeResolution(timeResolution) {}

    CapabilitySet getCapabilities() const override { return CapabilitySet{ Capability::AstrodynamicEnv}; }

    StateType computeNextState(StateType currentState,
        const ControlInputPlan<ControlInputType> &inputPlan) override;

    void resolveDependencies(const ComponentConfig &config, ComponentManager *manager) override;

protected:
    std::shared_ptr<IDynamicsSimulator<StateType>> dynamicsSimulator;
    std::shared_ptr<InternalForcesComputer<StateType, ControlInputType>> internalForcesComputer;
    std::shared_ptr<ExternalForcesComputer<StateType>> externalForcesComputer;
    std::shared_ptr<IForceToAccelerationConverter<StateType>> forceToAccelerationConverter;
private:
    double timeResolution;
};

template<typename StateType, typename ControlInputType>
StateType PhysicsSimulator<StateType, ControlInputType>::computeNextState(StateType initialState,
const ControlInputPlan<ControlInputType> &inputPlan)       //StateType shall be a const reference, but
{                                                          // const qualifier was removed for performance reasons
    StateType& currentState = initialState;
    for (const auto& segment : inputPlan.getSegments())
    {
        double timeLeft = segment.duration;
        while (timeLeft > 0)
        {
            double stepTime = std::min(timeLeft, timeResolution);
            TotalForce internal = internalForcesComputer->computeTotalForce(currentState, *(segment.controlInput.get()));
            TotalForce external = externalForcesComputer->computeTotalForce(currentState);
            TotalForce total = internal + external;
            TotalAcceleration acceleration = forceToAccelerationConverter->convert(total, currentState);
            currentState = dynamicsSimulator->computeNextState(currentState, acceleration,stepTime);
            timeLeft -= stepTime;
        }

    }
    return currentState;
}

template<typename StateType, typename ControlInputType>
void PhysicsSimulator<StateType, ControlInputType>::resolveDependencies(const ComponentConfig &config,
    ComponentManager *manager)
{
    IPhysicsSimulator<StateType, ControlInputType>::resolveDependencies(config, manager);
    dynamicsSimulator = std::dynamic_pointer_cast<IDynamicsSimulator<StateType>>(manager->getComponent(ComponentType::DynamicsSimulator));
    internalForcesComputer = std::dynamic_pointer_cast<InternalForcesComputer<StateType, ControlInputType>>(
        manager->getComponent(ComponentType::InternalForcesComputer));
    externalForcesComputer = std::dynamic_pointer_cast<ExternalForcesComputer<StateType>>(
        manager->getComponent(ComponentType::ExternalForcesComputer));
    forceToAccelerationConverter = std::dynamic_pointer_cast<IForceToAccelerationConverter<StateType>>(
        manager->getComponent(ComponentType::ForceToAccelerationConverter));
}


#endif //PHYSICSSIMULATOR_H
