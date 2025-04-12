//
// Created by arseniy on 12.4.25.
//

#include "AstrodynamicsSimulator.h"

#include <components/dynamicsSimulators/DynamicsSimulator.h>

std::unique_ptr<IComponent> AstrodynamicsSimulator::createComponent(const ComponentConfig &config,
                                                                    const ReaderContext &context)
{
    auto stateDynamicsSimulatorComponent = DynamicsSimulator::createComponent(config, context);

    if (auto* castPtr = dynamic_cast<DynamicsSimulator*>(stateDynamicsSimulatorComponent.get()))
    {
        stateDynamicsSimulatorComponent.release();
        std::unique_ptr<DynamicsSimulator> staticHandler(castPtr);
        return std::make_unique<AstrodynamicsSimulator>(std::move(staticHandler));
    }
    spdlog::error("Error when creating AstrodynamicsSimulator. Provided DynamicsSimulator is invalid");
    throw std::runtime_error("Error when creating AstrodynamicsSimulator. Provided DynamicsSimulator is invalid");
}

SpaceshipState AstrodynamicsSimulator::computeNextState(const SpaceshipState &currentState,
    const TotalAcceleration &totalAcceleration, double timestep)
{
    State computedState = stateSimulator->computeNextState(currentState, totalAcceleration, timestep);
    return SpaceshipState(computedState, currentState.getFuel()); // TODO create FuelComponent to handler fuel updates instead of this crunch
}
