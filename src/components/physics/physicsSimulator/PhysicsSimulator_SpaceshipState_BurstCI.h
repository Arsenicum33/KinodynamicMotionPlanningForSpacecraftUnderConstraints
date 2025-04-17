//
// Created by arseniy on 12.4.25.
//

#ifndef PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#define PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
#include "PhysicsSimulator.h"
#include "dto/poses/dynamic/kinodynamic/burstControlInput/BurstControlInput.h"

class PhysicsSimulator_SpaceshipState_BurstCI : public PhysicsSimulator<SpaceshipState, BurstControlInput>
{
public:
    PhysicsSimulator_SpaceshipState_BurstCI(double timeResolution) :
        PhysicsSimulator<SpaceshipState, BurstControlInput>(timeResolution) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    SpaceshipState computeNextState(const SpaceshipState& currentState,
        const ControlInputPlan<BurstControlInput> &inputPlan) override;
};

inline std::unique_ptr<IComponent> PhysicsSimulator_SpaceshipState_BurstCI::createComponent(
    const ComponentConfig &config, const ReaderContext &context)
{
    const auto& configMap = config.config;

    double timeResolution = std::any_cast<double>(configMap.at("timeResolution"));

    return std::make_unique<PhysicsSimulator_SpaceshipState_BurstCI>(timeResolution);
}

inline SpaceshipState PhysicsSimulator_SpaceshipState_BurstCI::computeNextState(const SpaceshipState& initialState,
    const ControlInputPlan<BurstControlInput> &inputPlan)
{
    SpaceshipState currentState = initialState;
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
            FuelState nextFuelState = fuelSystem->getNextFuelState(currentState.getFuel(), internal, stepTime);
            currentState = dynamicsSimulator->computeNextState(currentState, acceleration,stepTime);
            currentState.setFuel(nextFuelState);
            timeLeft -= stepTime;
        }

    }
    return currentState;
}

#endif //PHYSICSSIMULATOR_SPACESHIPSTATE_BURSTCI_H
