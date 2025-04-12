//
// Created by arseniy on 12.4.25.
//

#ifndef ASTRODYNAMICSSIMULATOR_H
#define ASTRODYNAMICSSIMULATOR_H
#include <components/dynamicsSimulators/IDynamicsSimulator.h>

#include "dto/poses/astrodynamic/spaceshipState/SpaceshipState.h"


class AstrodynamicsSimulator : public IDynamicsSimulator<SpaceshipState>
{
public:
    AstrodynamicsSimulator(std::unique_ptr<IDynamicsSimulator<State>> dynamicsSimulator) :
        stateSimulator(std::move(dynamicsSimulator)) {}
    static std::unique_ptr<IComponent> createComponent(const ComponentConfig &config, const ReaderContext &context);

    CapabilitySet getCapabilities() const override { return CapabilitySet { Capability::AstrodynamicEnv }; };

    SpaceshipState computeNextState(const SpaceshipState &currentState, const TotalAcceleration &totalAcceleration,
        double timestep) override;
private:
    std::unique_ptr<IDynamicsSimulator<State>> stateSimulator;
};



#endif //ASTRODYNAMICSSIMULATOR_H
